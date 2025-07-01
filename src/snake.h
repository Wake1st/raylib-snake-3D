#ifndef SNAKE_H
#define SNAKE_H

#include "stdlib.h"
#include "stdio.h"
#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "input.h"

typedef struct Snake
{
  bool isGrowing;
  Vector3 forward;
  Vector3 left;
  Vector3 up;
  Vector3 body[MAX_LENGTH];
  int tailIndex;
} Snake;

typedef struct RotationResult
{
  bool rotated;
  Vector3 axis;
} RotationResult;

Snake InitSnake(Vector3 start, Vector3 forward);
RotationResult MoveSnake(Snake *snake);
bool CheckSelfCollision(Snake *snake);
void FeedSnake(Snake *snake);
void DrawSnake(Snake *snake);

#endif
