#include "food.h"

void MoveFood(Food *food)
{
  food->position = (Vector3){
      (float)GetRandomValue(-LEVEL_SIZE / 2, LEVEL_SIZE / 2),
      (float)GetRandomValue(-LEVEL_SIZE / 2, LEVEL_SIZE / 2),
      (float)GetRandomValue(-LEVEL_SIZE / 2, LEVEL_SIZE / 2),
  };
}

int CheckEaten(Food *food, Snake *snake)
{
  return Vector3Equals(food->position, snake->body[0]);
}

void DrawFood(Food *food)
{
  DrawCubeV(food->position, SEGMENT_SIZE, GREEN);
}