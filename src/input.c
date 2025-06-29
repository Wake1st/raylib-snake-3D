#include "input.h"

Direction HandleInput()
{
  if (IsKeyDown(KEY_UP))
    return DIRECTION_UP;
  if (IsKeyDown(KEY_LEFT))
    return DIRECTION_LEFT;
  if (IsKeyDown(KEY_DOWN))
    return DIRECTION_DOWN;
  if (IsKeyDown(KEY_RIGHT))
    return DIRECTION_RIGHT;
  else
    return DIRECTION_NONE;
}