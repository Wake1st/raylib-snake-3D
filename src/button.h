#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

#include "globals.h"
#include "game_state.h"

#define BUTTON_FRAMES 3

typedef struct Button
{
  Texture2D texture;
  Rectangle rect;
  Rectangle position;
  float frameHeight;
  Sound fx;
  bool selected;
  GameState selectedState;
} Button;

Button InitButton(Texture2D text, Vector2 offset, Sound soundFx, GameState state);
void UpdateButton(Button *button);
void DrawButton(Button *button);

#endif
