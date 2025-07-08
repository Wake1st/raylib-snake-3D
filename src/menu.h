#ifndef MENU_H
#define MENU_H

#include "game_state.h"
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
GameState UpdateMainMenu(MainMenu *menu);
void DrawMainMenu(MainMenu *menu);

CreditsMenu InitCreditsMenu(Button *menuButton);
GameState UpdateCreditsMenu(CreditsMenu *menu);
void DrawCreditsMenu(CreditsMenu *menu);

ScoreMenu InitScoreMenu(Button *menu, Button *play);
GameState UpdateScoreMenu(ScoreMenu *menu);
void DrawScoreMenu(ScoreMenu *menu, int score);

#endif
