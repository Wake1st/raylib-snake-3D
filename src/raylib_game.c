/*******************************************************************************************
 *
 *   raylib gamejam template
 *
 *   Template originally created with raylib 4.5-dev, last time updated with raylib 5.0
 *
 *   Template licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2022-2025 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_WEB)
#define CUSTOM_MODAL_DIALOGS       // Force custom modal dialogs usage
#include <emscripten/emscripten.h> // Emscripten library - LLVM to JavaScript compiler
#endif

#include <stdio.h>  // Required for: printf()
#include <stdlib.h> // Required for:
#include <string.h> // Required for:

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#include "globals.h"
#include "game_state.h"
#include "menu.h"
#include "clock.h"
#include "snake.h"
#include "food.h"
#include "boundry.h"

// TODO: Define your custom data types here
typedef struct GameData
{
    Camera3D camera;
    Clock *clock;
    Snake *snake;
    Food *food;
    MainMenu *main;
    CreditsMenu *credits;
    ScoreMenu *score;
} GameData;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------

static RenderTexture2D target = {0}; // Render texture to render our game

// TODO: Define global variables here, recommended to make them static
static const Vector3 cameraNeckStart = (Vector3){0.f, 3.f, 6.f};

static GameState activeState = GAME_MENU;
static Vector3 cameraNeck = cameraNeckStart;
static float clockStartRate = 0.8f;
static int score = 0;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

static void SetupGame(GameData *data);
static void MenuState(MainMenu *menu);
static void CreditsState(CreditsMenu *menu);
static void ScoreState(ScoreMenu *menu);
static void PlayState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
// static void IntroState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
// static void OutroState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
static bool UpdateDrawFrame(GameData data);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
#if !defined(_DEBUG)
    SetTraceLogLevel(LOG_NONE); // Disable raylib trace log messages
#endif

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib gamejam template");
    SetWindowMonitor(0);

    SetExitKey(KEY_NULL);

    // TODO: Load resources / Initialize variables at this point

    Texture2D playTexture = LoadTexture("resources/play_button.png");
    Texture2D menuTexture = LoadTexture("resources/menu_button.png");
    Texture2D creditsTexture = LoadTexture("resources/credits_button.png");
    Texture2D exitTexture = LoadTexture("resources/exit_button.png");

    // Sound music = LoadSound("resources/snake.ogg");
    Sound blip = LoadSound("resources/blip_select.ogg");

    // UI   -------------------------------------------------
    Button playButton = InitButton(playTexture, (Vector2){.x = 0.f, .y = -360.f}, blip, GAME_PLAY);
    Button creditsButton = InitButton(creditsTexture, (Vector2){.x = 0.f, .y = -200.f}, blip, GAME_CREDITS);
    Button exitButton = InitButton(exitTexture, (Vector2){.x = 0.f, .y = -40.f}, blip, GAME_EXIT);
    Button menuButton = InitButton(menuTexture, (Vector2){.x = 0.f, .y = 360.f}, blip, GAME_MENU);

    MainMenu mainMenu = InitMainMenu(&playButton, &creditsButton, &exitButton);
    ScoreMenu scoreMenu = InitScoreMenu(&playButton, &menuButton);
    CreditsMenu creditsMenu = InitCreditsMenu(&menuButton);

    // PLAY -------------------------------------------------
    Vector3 start = (Vector3){0.f, 0.f, 2.f};
    Vector3 forward = (Vector3){0.f, 0.f, -1.f};

    Camera3D camera = {0};
    camera.position = cameraNeck;
    camera.target = start;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 85.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Snake snake = InitSnake(start, forward);
    Food food = (Food){
        .position = (Vector3){0.f, 0.f, 0.f},
    };

    // movement clock
    Clock clock = InitClock(clockStartRate);

    GameData gameData = (GameData){
        .camera = camera,
        .clock = &clock,
        .snake = &snake,
        .food = &food,
        .main = &mainMenu,
        .credits = &creditsMenu,
        .score = &scoreMenu,
    };

    // Render texture to draw full screen, enables screen scaling
    // NOTE: If screen is scaled, mouse input should be scaled proportionally
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loopbool UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60); // Set our game frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    bool exitWindow = false;
    while (!exitWindow)
    {
        UpdateDrawFrame(gameData);

        if (activeState == GAME_EXIT || WindowShouldClose())
            exitWindow = true;
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);

    // TODO: Unload all loaded resources at this point
    UnloadTexture(playTexture);
    UnloadTexture(menuTexture);
    UnloadTexture(creditsTexture);
    UnloadTexture(exitTexture);

    UnloadSound(blip);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------------
// Module functions definition
//--------------------------------------------------------------------------------------------
// Update and draw frame
bool UpdateDrawFrame(GameData data)
{
    switch (activeState)
    {
    case GAME_MENU:
    {
        MenuState(data.main);

        // setup game
        if (activeState == GAME_PLAY)
        {
            SetupGame(&data);
        }

        break;
    }
    case GAME_CREDITS:
    {
        CreditsState(data.credits);
        break;
    }
    case GAME_INTRO:
    {

        break;
    }
    case GAME_PLAY:
    {
        PlayState(data.camera, data.clock, data.snake, data.food);
        break;
    }
    case GAME_SCORE:
    {
        ScoreState(data.score);

        // setup game
        if (activeState == GAME_PLAY)
        {
            SetupGame(&data);
        }

        break;
    }
    case GAME_OUTRO:
    {

        break;
    }
    case GAME_EXIT:
    {
        return true;
    }
    case GAME_NONE:
    {
        break;
    }
    }

    return false;
}

void SetupGame(GameData *data)
{
    Vector3 start = (Vector3){0.f, 0.f, 2.f};
    Vector3 forward = (Vector3){0.f, 0.f, -1.f};

    data->camera.position = cameraNeck;
    data->camera.target = start;
    data->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    cameraNeck = cameraNeckStart;

    // movement clock
    ResetSnake(data->snake, start, forward);
    ResetClock(data->clock, clockStartRate);

    MoveFood(data->food);
}

void MenuState(MainMenu *menu)
{
    // Update
    GameState selectedState = UpdateMainMenu(menu);
    if (selectedState != GAME_NONE)
    {
        activeState = selectedState;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawMainMenu(menu);

    EndDrawing();
}

void CreditsState(CreditsMenu *menu)
{
    // Update
    GameState selectedState = UpdateCreditsMenu(menu);
    if (selectedState != GAME_NONE)
    {
        activeState = selectedState;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCreditsMenu(menu);

    EndDrawing();
}

void ScoreState(ScoreMenu *menu)
{
    // Update
    GameState selectedState = UpdateScoreMenu(menu);
    if (selectedState != GAME_NONE)
    {
        activeState = selectedState;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawScoreMenu(menu, score);

    EndDrawing();
}

void PlayState(Camera3D camera, Clock *clock, Snake *snake, Food *food)
{
    // Update
    //----------------------------------------------------------------------------------
    if (TickClock(clock))
    {
        // move snake
        RotationResult result = MoveSnake(snake);
        if (result.rotated)
        {
            cameraNeck = Vector3RotateByAxisAngle(cameraNeck, result.axis, PI / 2);
        }

        // check collisions
        if (CheckSelfCollision(snake) || CheckBoundry(snake))
        {
            // GAME OVER
            activeState = GAME_SCORE;
        }

        // feed the snake
        if (CheckEaten(food, snake) == 1)
        {
            FeedSnake(snake);
            MoveFood(food);
            DecreaseClockRate(clock);
            score++;
        }
    }

    camera.position = Vector3Add(snake->body[0], cameraNeck);
    camera.target = Vector3Add(camera.position, snake->forward);
    camera.up = snake->up;
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);

    // Draw
    //----------------------------------------------------------------------------------

    // Render to screen (main framebuffer)
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    // Draw render texture to screen, scaled if required
    DrawSnake(snake);
    DrawFood(food);
    DrawBoundry();

    EndMode3D();
    // TODO: Draw everything that requires to be drawn at this point, maybe UI?

    EndDrawing();
    //----------------------------------------------------------------------------------
}