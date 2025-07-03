#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

#include "globals.h"

#define BUTTON_FRAMES 3

typedef struct Button
{
  Texture2D texture;
  Rectangle rect;
  Rectangle bounds;
  Sound fx;
  bool selected;
} Button;

static float frameHeight;

Button InitButton(Texture2D text, Sound soundFx);
void UpdateButton(Button *button);
void DrawButton(Button *button);

#endif
