#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Globals.h"
#include "menu/MainMenu.h"
#include "menu/GameoverMenu.h"
#include "Snake.h"
#include "util/sfml_addon.h"

int              highscore = 0;
int              lastscore = 0;

GameState game_state = GAME_STATE_MAIN_MENU;

Snake   snake(SCREEN_WIDTH/GRID_SCALE, SCREEN_HEIGHT/GRID_SCALE);
MainMenu    mainMenu(SCREEN_WIDTH,SCREEN_HEIGHT);
GameoverMenu    gameoverMenu(SCREEN_WIDTH,SCREEN_HEIGHT);

int main()
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(50);
    sf::View view;
    view.setSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );
    view = getLetterboxView( view, SCREEN_WIDTH, SCREEN_HEIGHT );  

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    return 0;
                }                
                case sf::Event::Resized:
                {
                    view = getLetterboxView( view, event.size.width, event.size.height );
                    break;
                }
            }


            
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                {
                    switch (game_state)
                    {
                        case GAME_STATE_INGAME:         snake.onKeyPress(event);      break;
                        case GAME_STATE_MAIN_MENU:      mainMenu.onKeyPressed(event); break;
                        case GAME_STATE_MENU_GAMEOVER:  gameoverMenu.onKeyPressed(event); break;
                    }
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    switch (game_state)
                    {
                        case GAME_STATE_MAIN_MENU:      mainMenu.onMouseMove(event); break;
                        case GAME_STATE_MENU_GAMEOVER:  gameoverMenu.onMouseMove(event); break;
                    }
                    break;
                } 
                case sf::Event::MouseButtonPressed:
                {
                    switch (game_state)
                    {
                        case GAME_STATE_MAIN_MENU:      mainMenu.onMouseClick(event); break;
                        case GAME_STATE_MENU_GAMEOVER:  gameoverMenu.onMouseClick(event); break;
                    }                    
                    break;
                } 
            }
        }
        if(game_state == GAME_STATE_EXIT)
        {
            window.close();
            return 0;
        }
        
        window.clear();
        window.setView(view); 
        
        switch (game_state)
        {
            case GAME_STATE_INGAME:         snake.render(window);    break;
            case GAME_STATE_MAIN_MENU:      mainMenu.render(window); break;
            case GAME_STATE_MENU_GAMEOVER:  gameoverMenu.render(window); break;
        }
        window.display();
    }

    return 0;
}