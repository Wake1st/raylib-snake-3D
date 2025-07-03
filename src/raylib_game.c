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

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum
{
    SCREEN_LOGO = 0,
    SCREEN_TITLE,
    SCREEN_GAMEPLAY,
    SCREEN_ENDING
} GameScreen;

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------

static RenderTexture2D target = {0}; // Render texture to render our game

// TODO: Define global variables here, recommended to make them static
static Vector3 cameraNeck = (Vector3){0.f, 3.f, 6.f};

static GameState ActiveState = GAME_MENU;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

static void MenuState();
static void PlayState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
// static void IntroState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
// static void OutroState(Camera3D camera, Clock *clock, Snake *snake, Food *food);
static void UpdateDrawFrame(Camera3D camera, Clock *clock, Snake *snake, Food *food);

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

    // TODO: Load resources / Initialize variables at this point

    Texture2D playTexture = LoadTexture("resources/play_button.png");
    Texture2D menuTexture = LoadTexture("resources/menu_button.png");
    Texture2D creditsTexture = LoadTexture("resources/credits_button.png");
    Texture2D exitTexture = LoadTexture("resources/exit_button.png");

    Sound music = LoadSound("resources/snake.ogg");
    Sound blip = LoadSound("resources/blip_select.ogg");

    // UI   -------------------------------------------------
    Button playButton = InitButton(playTexture, blip);
    Button creditsButton = InitButton(creditsTexture, blip);
    Button exitButton = InitButton(exitTexture, blip);
    Button menuButton = InitButton(menuTexture, blip);

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
    Clock clock = InitClock(1.f);

    // Render texture to draw full screen, enables screen scaling
    // NOTE: If screen is scaled, mouse input should be scaled proportionally
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60); // Set our game frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button
    {
        UpdateDrawFrame(camera, &clock, &snake, &food);
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);

    // TODO: Unload all loaded resources at this point

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------------
// Module functions definition
//--------------------------------------------------------------------------------------------
// Update and draw frame
void UpdateDrawFrame(Camera3D camera, Clock *clock, Snake *snake, Food *food)
{
    switch (ActiveState)
    {
    case GAME_MENU:
    {
        MenuState(camera, clock, snake, food);
        break;
    }
    case GAME_INTRO:

        break;
    case GAME_PLAY:
    {
        PlayState(camera, clock, snake, food);
        break;
    }
    case GAME_OUTRO:

        break;
    }
}

void MenuState()
{
    // Update
    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

void PlayState(Camera3D camera, Clock *clock, Snake *snake, Food *food)
{
    // Update
    //----------------------------------------------------------------------------------
    if (TickClock(clock))
    {
        // move snake
        // printf("\nmoving...");
        // fflush(stdout);
        RotationResult result = MoveSnake(snake);
        if (result.rotated)
        {
            cameraNeck = Vector3RotateByAxisAngle(cameraNeck, result.axis, PI / 2);
        }

        // check collisions
        // printf("\tchecking collision...");
        // fflush(stdout);
        if (CheckSelfCollision(snake) || CheckBoundry(snake))
        {
            // GAME OVER
            printf("\n - collided! - \n");
            fflush(stdout);
        }

        // feed the snake
        // printf(TextFormat(
        //     "\t{%f,%f,%f} == {%f,%f,%f}",
        // food->position.x, food->position.x, food->position.x,
        // (snake->body[0]).x, (snake->body[0]).y, (snake->body[0]).z));
        // fflush(stdout);
        if (CheckEaten(food, snake) == 1)
        {
            // printf("\twas eaten");
            // fflush(stdout);
            FeedSnake(snake);
            MoveFood(food);
            DecreaseClockRate(clock);
        }
        // printf("\tpost food");
        // fflush(stdout);
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