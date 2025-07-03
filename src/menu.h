#ifndef MENU_H
#define MENU_H

#include "button.h"

#define MENU_BUTTON_COUNT 3
#define SCORE_BUTTON_COUNT 2

typedef struct MainMenu
{
  Button *buttons[MENU_BUTTON_COUNT];
} MainMenu;

typedef struct CreditsMenu
{
  Button *button;
} CreditsMenu;

typedef struct ScoreMenu
{
  Button *buttons[SCORE_BUTTON_COUNT];
} ScoreMenu;

MainMenu InitMainMenu(Button *play, Button *credits, Button *exit);
void UpdateMainMenu(MainMenu *menu);
void DrawMainMenu(MainMenu *menu);

CreditsMenu InitCreditsMenu(Button *menuButton);
void UpdateCreditsMenu(CreditsMenu *menu);
void DrawCreditsMenu(CreditsMenu *menu);

ScoreMenu InitScoreMenu(Button *menu, Button *play);
void UpdateScoreMenu(ScoreMenu *menu);
void DrawScoreMenu(ScoreMenu *menu);

#endif
