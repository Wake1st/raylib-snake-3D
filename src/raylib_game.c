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
#include "clock.h"
#include "snake.h"
#include "food.h"

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
static const int screenWidth = 1200;
static const int screenHeight = 900;

static RenderTexture2D target = {0}; // Render texture to render our game

// TODO: Define global variables here, recommended to make them static
static Vector3 cameraNeck = (Vector3){0.f, 2.f, 4.f};

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(Camera3D camera, Clock *clock, Snake *snake, Food *food); // Update and Draw one frame

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

    // Define the camera to look into our 3d world
    Vector3 start = (Vector3){0.f, 0.f, 2.f};
    Vector3 forward = (Vector3){0.f, 0.f, -1.f};

    Camera3D camera = {0};
    camera.position = cameraNeck;            // Camera position
    camera.target = start;                   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    camera.fovy = 85.0f;                     // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

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
        bool self = CheckSelfCollision(snake);
        if (self)
        {
            // printf("\tself collided!");
            // fflush(stdout);
            // GAME OVER
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
    // Render game screen to a texture,
    // it could be useful for scaling or further shader postprocessing
    // BeginTextureMode(target);
    // ClearBackground(RAYWHITE);

    // // TODO: Draw your game screen here
    // DrawText("Welcome to raylib NEXT gamejam!", 150, 140, 30, BLACK);
    // DrawRectangleLinesEx((Rectangle){0, 0, screenWidth, screenHeight}, 16, BLACK);

    // EndTextureMode();

    // Render to screen (main framebuffer)
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    // Draw render texture to screen, scaled if required
    DrawSnake(snake);
    DrawFood(food);
    DrawGrid(16, 1.0f);

    EndMode3D();
    // TODO: Draw everything that requires to be drawn at this point, maybe UI?

    EndDrawing();
    //----------------------------------------------------------------------------------
}
