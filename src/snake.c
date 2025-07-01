#include "snake.h"

Snake InitSnake(Vector3 *start, Vector3 forward)
{
  return (Snake){
      .isGrowing = false,
      .forward = forward,
      .left = (Vector3){-1.f, 0.f, 0.f},
      .up = (Vector3){0.f, 1.f, 0.f},
      .tailIndex = 0,
      .body[0] = start,
  };
}

RotationResult MoveSnake(Snake *snake)
{
  // setup result
  RotationResult result = {
      .rotated = false,
      .axis = (Vector3){0.f, 0.f, 0.f},
  };

  // accept input
  Direction input = HandleInput();

  // calculate next step
  Vector3 currentHead = *snake->body[0];
  Vector3 next = (Vector3){0.f, 0.f, 0.f};

  switch (input)
  {
  case DIRECTION_UP:
  {
    next = Vector3Add(currentHead, snake->up);

    Vector3 oldUP = snake->up;
    snake->up = Vector3Scale(snake->forward, -1.f);
    snake->forward = oldUP;

    result.rotated = true;
    result.axis = Vector3Scale(snake->left, -1.f);

    break;
  }
  case DIRECTION_LEFT:
  {
    next = Vector3Add(currentHead, snake->left);

    Vector3 oldLeft = snake->left;
    snake->left = Vector3Scale(snake->forward, -1.f);
    snake->forward = oldLeft;

    result.rotated = true;
    result.axis = snake->up;

    break;
  }
  case DIRECTION_DOWN:
  {
    next = Vector3Add(currentHead, Vector3Scale(snake->up, -1.f));

    Vector3 oldUP = snake->up;
    snake->up = snake->forward;
    snake->forward = Vector3Scale(oldUP, -1.f);

    result.rotated = true;
    result.axis = snake->left;

    break;
  }
  case DIRECTION_RIGHT:
  {
    next = Vector3Add(currentHead, Vector3Scale(snake->left, -1.f));

    Vector3 oldLeft = snake->left;
    snake->left = snake->forward;
    snake->forward = Vector3Scale(oldLeft, -1.f);

    result.rotated = true;
    result.axis = Vector3Scale(snake->up, -1.f);

    break;
  }
  case DIRECTION_NONE:
  default:
  {
    next = Vector3Add(currentHead, snake->forward);
    break;
  }
  }

  for (int i = 0; i <= snake->tailIndex; i++)
  {
    // don't move the tail if growing
    if (i == snake->tailIndex && snake->isGrowing)
    {
      snake->isGrowing = false;
    }
    else
    {
      Vector3 temp = *snake->body[i];
      *snake->body[i] = next;
      next = temp;
    }
  }

  return result;
}

bool CheckSelfCollision(Snake *snake)
{
  Vector3 head = *snake->body[0];
  for (int i = 1; i <= snake->tailIndex; i++)
  {
    if (Vector3Equals(head, *snake->body[i]))
    {
      return true;
    }
  }
  return false;
}

void FeedSnake(Snake *snake)
{
  Vector3 tail = *snake->body[snake->tailIndex++];
  *snake->body[snake->tailIndex] = tail;
  snake->isGrowing = true;
}

void DrawSnake(Snake *snake)
{
  for (int i = 0; i <= snake->tailIndex; i++)
  {
    DrawCubeV(*snake->body[i], SEGMENT_SIZE, PURPLE);
  }
}