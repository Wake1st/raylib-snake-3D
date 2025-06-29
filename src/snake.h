#ifndef SNAKE_H
#define SNAKE_H

#include "stdio.h"
#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "input.h"

static const Vector3 SEGMENT_SIZE = (Vector3){CELL_SIZE, CELL_SIZE, CELL_SIZE};

typedef struct Snake
{
  bool isGrowing;
  Vector3 forward;
  Vector3 left;
  Vector3 up;
  Vector3 *body[MAX_CELLS];
  int tailIndex;
} Snake;

Snake InitSnake(Vector3 *start, Vector3 forward);
void MoveSnake(Snake *snake);
bool CheckSelfCollision(Snake *snake);
void FeedSnake(Snake *snake);
void DrawSnake(Snake *snake);

#endif
