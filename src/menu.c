#include "menu.h"

MainMenu InitMainMenu(Button *play, Button *credits, Button *exit)
{
  return (MainMenu){
      .buttons = {
          play,
          credits,
          exit}};
}

void UpdateMainMenu(MainMenu *menu)
{
  for (int i = 0; i < MENU_BUTTON_COUNT; i++)
  {
    UpdateButton(menu->buttons[i]);
  }
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

void UpdateCreditsMenu(CreditsMenu *menu)
{
  UpdateButton(menu->button);
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

void UpdateScoreMenu(ScoreMenu *menu)
{
  for (int i = 0; i < SCORE_BUTTON_COUNT; i++)
  {
    UpdateButton(menu->buttons[i]);
  }
}

void DrawScoreMenu(ScoreMenu *menu)
{
  for (int i = 0; i < SCORE_BUTTON_COUNT; i++)
  {
    DrawButton(menu->buttons[i]);
  }
}
