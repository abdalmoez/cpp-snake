#include "menu/GameoverMenu.h"
#include <sstream>
GameoverMenu::GameoverMenu(int width, int height):
    m_width(width)
    ,m_height(height)
{
    { 
        m_menuItems[MENU_ITEM_GAMEOVER].setFont(getDefaultFont());
        m_menuItems[MENU_ITEM_GAMEOVER].setFillColor(HOVER_COLOR);
        m_menuItems[MENU_ITEM_GAMEOVER].setScale(3,3);
        m_menuItems[MENU_ITEM_GAMEOVER].setString("GAMEOVER");    
        auto item_width = m_menuItems[MENU_ITEM_GAMEOVER].getLocalBounds().width;
        m_menuItems[MENU_ITEM_GAMEOVER].setPosition(sf::Vector2f((m_width - item_width*3)  / 2, m_height / 4 * 1));
    }

    {
        m_menuItems[MENU_ITEM_HIGHSCORE].setFont(getDefaultFont());
        m_menuItems[MENU_ITEM_HIGHSCORE].setFillColor(IDLE_COLOR);
    }
    
    
    {
        m_menuItems[MENU_ITEM_SCORE].setFont(getDefaultFont());
        m_menuItems[MENU_ITEM_SCORE].setFillColor(IDLE_COLOR);
    }

    {
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setFont(getDefaultFont());
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setFillColor(IDLE_COLOR);
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setString("Return to menu");
        auto item_width = m_menuItems[MENU_ITEM_RETURN_TO_MENU].getLocalBounds().width;
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setPosition(sf::Vector2f((m_width - item_width)  / 2, m_height / 4 * 3));
    }

    m_selectedIndex = 0;
}
void GameoverMenu::onKeyPressed(sf::Event& event)
{
    
    if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
    {
        m_selectedIndex=MENU_ITEM_RETURN_TO_MENU;
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setFillColor(HOVER_COLOR);
    }
    if(event.key.code == sf::Keyboard::Return && m_selectedIndex != -1)
    {
        onSelectMenuItem();
    }
}
void GameoverMenu::onSelectMenuItem()
{
    switch (m_selectedIndex)
    {
        case MENU_ITEM_RETURN_TO_MENU:  game_state = GAME_STATE_MAIN_MENU; break;
    }
}
void GameoverMenu::onMouseMove(sf::Event& event)
{   
    if(m_menuItems[MENU_ITEM_RETURN_TO_MENU].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y))
    {
        m_selectedIndex=MENU_ITEM_RETURN_TO_MENU;
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setFillColor(HOVER_COLOR);
    }
    else
    {
        m_selectedIndex = -1;
        m_menuItems[MENU_ITEM_RETURN_TO_MENU].setFillColor(IDLE_COLOR);
    }
}
void GameoverMenu::onMouseClick(sf::Event& event)
{
    int target_menu_item = -1;
    for(int i=0;i<TOTAL_MENU_ITEMS;i++)
    {
        if(m_menuItems[i].getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
        {
            target_menu_item = i;
            break;
        }
    }
    if(target_menu_item == -1)
    {
        return;
    }

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        m_menuItems[m_selectedIndex].setFillColor(IDLE_COLOR);
        m_selectedIndex=target_menu_item;
        m_menuItems[m_selectedIndex].setFillColor(HOVER_COLOR);
        onSelectMenuItem();
    }

}
void GameoverMenu::render(sf::RenderWindow &window)
{

    {
        std::stringstream ss;
        ss<<"Your score: "<<lastscore;
        m_menuItems[MENU_ITEM_SCORE].setString(ss.str());
        auto item_width = m_menuItems[MENU_ITEM_SCORE].getLocalBounds().width;
        m_menuItems[MENU_ITEM_SCORE].setPosition(sf::Vector2f((m_width - item_width)  / 2, m_height / 4 * 2.4));
    }

    {
        std::stringstream ss;
        ss<<"Highscore: "<<highscore;
        m_menuItems[MENU_ITEM_HIGHSCORE].setString(ss.str());
        auto item_width = m_menuItems[MENU_ITEM_HIGHSCORE].getLocalBounds().width;
        m_menuItems[MENU_ITEM_HIGHSCORE].setPosition(sf::Vector2f((m_width - item_width)  / 2, m_height / 4 * 2));
    }
    for(int i=0;i<TOTAL_MENU_ITEMS;i++)
    {
        window.draw(m_menuItems[i]);
    }
    
}