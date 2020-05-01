#ifndef GLOBALS_H
#define GLOBALS_H

#include "GameState.h"
#include "MainMenu.hpp"

#define WINDOW_TITLE "CPP Snake"
#define WIDTH  640
#define HEIGHT 480
#define SCALE  32

GameState game_state;

Snake   snake(WIDTH/SCALE, HEIGHT/SCALE);
MainMenu    mainMenu(WIDTH,HEIGHT);

#endif