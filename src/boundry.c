#include "boundry.h"

bool CheckBoundry(Snake *snake)
{
  return snake->body[0].x == BOUND / 2 || snake->body[0].x == -BOUND / 2 || snake->body[0].y == BOUND / 2 || snake->body[0].y == -BOUND / 2 || snake->body[0].z == BOUND / 2 || snake->body[0].z == -BOUND / 2;
}

void DrawBoundry()
{
  // ceiling
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){i - BOUND / 2, j - BOUND / 2, BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }

  // floor
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){i - BOUND / 2, j - BOUND / 2, -BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }

  // front
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){i - BOUND / 2, BOUND / 2, j - BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }

  // back
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){i - BOUND / 2, -BOUND / 2, j - BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }

  // right
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){BOUND / 2, j - BOUND / 2, i - BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }

  // left
  for (int i = 0; i < BOUND; i++)
  {
    for (int j = 0; j < BOUND; j++)
    {
      DrawSphereEx((Vector3){-BOUND / 2, j - BOUND / 2, i - BOUND / 2}, RADIUS, RINGS, SLICES, RED);
    }
  }
}
