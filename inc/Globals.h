#ifndef GLOBALS_H
#define GLOBALS_H

#include "GameState.h"


extern GameState    game_state;

class Snake;
class MainMenu;
class GameoverMenu;

extern Snake            snake;
extern MainMenu         mainMenu;
extern GameoverMenu     gameoverMenu;

extern int              highscore;
extern int              lastscore;

#endif