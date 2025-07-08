#include "button.h"

Button InitButton(Texture2D text, Vector2 offset, Sound soundFx, GameState state)
{
  // Define frame rectangle for drawing
  float height = (float)text.height / BUTTON_FRAMES;
  Rectangle sourceRec = {0, 0, (float)text.width, height};

  // Define button position on screen
  Rectangle btnPosition = {
      screenWidth / 2.0f - text.width / 2.0f + offset.x,
      screenHeight / 2.0f - text.height / BUTTON_FRAMES / 2.0f + offset.y,
      (float)text.width,
      height};

  return (Button){
      .texture = text,
      .rect = sourceRec,
      .position = btnPosition,
      .frameHeight = height,
      .fx = soundFx,
      .selected = false,
      .selectedState = state,
  };
}

void UpdateButton(Button *button)
{
  // Reset selection
  button->selected = false;

  int btnState = 0;       // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
  bool btnAction = false; // Button action should be activated

  Vector2 mousePoint = {0.0f, 0.0f};

  mousePoint = GetMousePosition();
  btnAction = false;

  // Check button state
  if (CheckCollisionPointRec(mousePoint, button->position))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      btnState = 2;
    else
      btnState = 1;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
      btnAction = true;
  }
  else
    btnState = 0;

  if (btnAction)
  {
    button->selected = true;
    PlaySound(button->fx);
  }

  // Calculate button frame rectangle to draw depending on button state
  button->rect.y = btnState * button->frameHeight;
}

void DrawButton(Button *button)
{
  DrawTextureRec(button->texture, button->rect, (Vector2){button->position.x, button->position.y}, WHITE);
}
