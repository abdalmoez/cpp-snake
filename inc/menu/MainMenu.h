#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "util/sfml_addon.h"

class MainMenu {
        enum{
            MENU_ITEM_PLAY,
            MENU_ITEM_OPTIONS,
            MENU_ITEM_EXIT,
            TOTAL_MENU_ITEMS
        };
    public:
        MainMenu(int width, int height);
        void onKeyPressed(sf::Event& event);
        void onSelectMenuItem();
        void onMouseMove(sf::Event& event);
        void onMouseClick(sf::Event& event);
        void render(sf::RenderWindow &window);
    private:
        sf::Text m_menuItems[TOTAL_MENU_ITEMS];
        int m_selectedIndex;
        const sf::Color IDLE_COLOR = sf::Color::White;
        const sf::Color HOVER_COLOR = sf::Color::Red;
};
#endif