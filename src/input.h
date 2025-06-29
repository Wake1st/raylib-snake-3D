#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

typedef enum Direction
{
  DIRECTION_NONE,
  DIRECTION_UP,
  DIRECTION_LEFT,
  DIRECTION_DOWN,
  DIRECTION_RIGHT,
} Direction;

Direction HandleInput(void);

#endif
