#include "button.h"

Button InitButton(Texture2D text, Sound soundFx)
{
  // Define frame rectangle for drawing
  frameHeight = (float)text.height / BUTTON_FRAMES;
  Rectangle sourceRec = {0, 0, (float)text.width, frameHeight};

  // Define button bounds on screen
  Rectangle btnBounds = {screenWidth / 2.0f - text.width / 2.0f, screenHeight / 2.0f - text.height / BUTTON_FRAMES / 2.0f, (float)text.width, frameHeight};

  return (Button){
      .texture = text,
      .rect = sourceRec,
      .bounds = btnBounds,
      .fx = soundFx,
      .selected = false,
  };
}

void UpdateButton(Button *button)
{
  // Reset selection
  button->selected = true;

  int btnState = 0;       // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
  bool btnAction = false; // Button action should be activated

  Vector2 mousePoint = {0.0f, 0.0f};

  mousePoint = GetMousePosition();
  btnAction = false;

  // Check button state
  if (CheckCollisionPointRec(mousePoint, button->bounds))
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
  button->rect.y = btnState * frameHeight;
}

void DrawButton(Button *button)
{
  DrawTextureRec(button->texture, button->rect, (Vector2){button->bounds.x, button->bounds.y}, WHITE);
}
