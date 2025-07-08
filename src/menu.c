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

void DrawScoreMenu(ScoreMenu *menu)
{
  for (int i = 0; i < SCORE_BUTTON_COUNT; i++)
  {
    DrawButton(menu->buttons[i]);
  }
}
