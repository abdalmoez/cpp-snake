#ifndef GAMEOVER_MENU_H
#define GAMEOVER_MENU_H

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "util/sfml_addon.h"

class GameoverMenu {
        enum{
            MENU_ITEM_RETURN_TO_MENU,
            MENU_ITEM_GAMEOVER,
            MENU_ITEM_SCORE,
            MENU_ITEM_HIGHSCORE,
            TOTAL_MENU_ITEMS
        };
    public:
        GameoverMenu(int width, int height);
        void onKeyPressed(sf::Event& event);
        void onSelectMenuItem();
        void onMouseMove(sf::Event& event);
        void onMouseClick(sf::Event& event);
        void render(sf::RenderWindow &window);
    private:
        sf::Font m_font;
        sf::Text m_menuItems[TOTAL_MENU_ITEMS];
        int m_selectedIndex;
        const sf::Color IDLE_COLOR = sf::Color::White;
        const sf::Color HOVER_COLOR = sf::Color::Red;

        const int m_width ;
        const int m_height;
};
#endif