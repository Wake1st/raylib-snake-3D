#ifndef SPAWNER_H
#define SPAWNER_H

#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "snake.h"

typedef struct Food
{
  Vector3 position;
} Food;

void MoveFood(Food *food);
int CheckEaten(Food *food, Snake *snake);
void DrawFood(Food *food);

#endif
