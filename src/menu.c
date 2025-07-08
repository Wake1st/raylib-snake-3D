#include "menu.h"

MainMenu InitMainMenu(Button *play, Button *credits, Button *exit)
{
  return (MainMenu){
      .buttons = {
          play,
          credits,
          exit}};
}

GameState UpdateMainMenu(MainMenu *menu)
{
  // update each button
  for (int i = 0; i < MENU_BUTTON_COUNT; i++)
  {
    UpdateButton(menu->buttons[i]);

    // return if selected
    if (menu->buttons[i]->selected)
    {
      return menu->buttons[i]->selectedState;
    }
  }

  // return nothing selected
  return GAME_NONE;
}

void DrawMainMenu(MainMenu *menu)
{
  for (int i = 0; i < MENU_BUTTON_COUNT; i++)
  {
    DrawButton(menu->buttons[i]);
  }

  DrawText("Controls", screenWidth / 2 - 180, screenHeight / 2 + 140, 80, BLACK);
  DrawText("Arrow Keys / WASD", screenWidth / 2 - 410, screenHeight / 2 + 240, 80, BLACK);
}

CreditsMenu InitCreditsMenu(Button *menuButton)
{
  return (CreditsMenu){
      .button = menuButton,
  };
}

GameState UpdateCreditsMenu(CreditsMenu *menu)
{
  // check for button selection
  UpdateButton(menu->button);

  // return if selected
  if (menu->button->selected)
  {
    return menu->button->selectedState;
  }

  // return nothing selected
  return GAME_NONE;
}

void DrawCreditsMenu(CreditsMenu *menu)
{
  DrawButton(menu->button);

  DrawText("Game", screenWidth / 2 - 100, screenHeight / 2 - 440, 80, BLACK);
  DrawText("by", screenWidth / 2 - 50, screenHeight / 2 - 340, 80, BLACK);
  DrawText("Joel Wakefield", screenWidth / 2 - 290, screenHeight / 2 - 240, 80, BLACK);

  DrawText("Raylib", screenWidth / 2 - 120, screenHeight / 2 - 100, 80, BLACK);
  DrawText("by", screenWidth / 2 - 50, screenHeight / 2, 80, BLACK);
  DrawText("Ramon Santamaria", screenWidth / 2 - 370, screenHeight / 2 + 100, 80, BLACK);
}

ScoreMenu InitScoreMenu(Button *menu, Button *play)
{
  return (ScoreMenu){
      .buttons = {
          menu,
          play},
  };
}

GameState UpdateScoreMenu(ScoreMenu *menu)
{
  // check for button selection
  for (int i = 0; i < SCORE_BUTTON_COUNT; i++)
  {
    UpdateButton(menu->buttons[i]);

    // return if selected
    if (menu->buttons[i]->selected)
    {
      return menu->buttons[i]->selectedState;
    }
  }

  // return nothing selected
  return GAME_NONE;
}

void DrawScoreMenu(ScoreMenu *menu, int score)
{
  for (int i = 0; i < SCORE_BUTTON_COUNT; i++)
  {
    DrawButton(menu->buttons[i]);
  }

  DrawText(TextFormat("SCORE: %d", score), screenWidth / 2 - 200, screenHeight / 2 - 40, 80, BLACK);
}
