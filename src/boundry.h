#ifndef BOUNDRY_H
#define BOUNDRY_H

#include "raylib.h"

#include "snake.h"

static const int BOUND = LEVEL_SIZE + 1;

static const float RADIUS = 0.2f;
static const int RINGS = 4;
static const int SLICES = 4;

bool CheckBoundry(Snake *snake);
void DrawBoundry();

#endif
