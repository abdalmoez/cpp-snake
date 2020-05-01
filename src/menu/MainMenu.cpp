#include "menu/MainMenu.h"
#include "Snake.h"
MainMenu::MainMenu(int width, int height)
{
    m_menuItems[MENU_ITEM_PLAY].setFont(getDefaultFont());
    m_menuItems[MENU_ITEM_PLAY].setFillColor(HOVER_COLOR);
    m_menuItems[MENU_ITEM_PLAY].setString("Play");
    auto item_width = m_menuItems[MENU_ITEM_PLAY].getLocalBounds().width;
    m_menuItems[MENU_ITEM_PLAY].setPosition(sf::Vector2f((width - item_width)  / 2, height / 4 * 1));

    m_menuItems[MENU_ITEM_OPTIONS].setFont(getDefaultFont());
    m_menuItems[MENU_ITEM_OPTIONS].setFillColor(IDLE_COLOR);
    m_menuItems[MENU_ITEM_OPTIONS].setString("Options");
    item_width = m_menuItems[MENU_ITEM_OPTIONS].getLocalBounds().width;
    m_menuItems[MENU_ITEM_OPTIONS].setPosition(sf::Vector2f((width - item_width)  / 2, height / 4 * 2));

    m_menuItems[MENU_ITEM_EXIT].setFont(getDefaultFont());
    m_menuItems[MENU_ITEM_EXIT].setFillColor(IDLE_COLOR);
    m_menuItems[MENU_ITEM_EXIT].setString("Exit");
    item_width = m_menuItems[MENU_ITEM_EXIT].getLocalBounds().width;
    m_menuItems[MENU_ITEM_EXIT].setPosition(sf::Vector2f((width - item_width)  / 2, height / 4 * 3));

    m_selectedIndex = 0;
    
}
void MainMenu::onKeyPressed(sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Up:
        {
            if(m_selectedIndex > 0)
            {
                m_menuItems[m_selectedIndex--].setFillColor(IDLE_COLOR);
                m_menuItems[m_selectedIndex].setFillColor(HOVER_COLOR);
            }
            break;
        }
        case sf::Keyboard::Down:
        {
            if(m_selectedIndex < TOTAL_MENU_ITEMS - 1)
            {
                m_menuItems[m_selectedIndex++].setFillColor(IDLE_COLOR);
                m_menuItems[m_selectedIndex].setFillColor(HOVER_COLOR);
            }
            break;
        }
        case sf::Keyboard::Return:
        {
            onSelectMenuItem();
            break;
        }
    }
}
void MainMenu::onSelectMenuItem()
{
    switch (m_selectedIndex)
    {
        case MENU_ITEM_PLAY:
        {
            snake.Init();
            game_state = GAME_STATE_INGAME;
            break;
        }
        case MENU_ITEM_EXIT:
        {
            game_state = GAME_STATE_EXIT;
            break;
        }
    }
}
void MainMenu::onMouseMove(sf::Event& event)
{   
    for(int i=0;i<TOTAL_MENU_ITEMS;i++)
    {
        if(m_menuItems[i].getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y))
        {
            m_menuItems[m_selectedIndex].setFillColor(IDLE_COLOR);
            m_selectedIndex=i;
            m_menuItems[m_selectedIndex].setFillColor(HOVER_COLOR);
            return;
        }
    }
    if(m_selectedIndex != -1)
    {
        m_menuItems[m_selectedIndex].setFillColor(IDLE_COLOR);
        m_selectedIndex = -1;
    }

}
void MainMenu::onMouseClick(sf::Event& event)
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
void MainMenu::render(sf::RenderWindow &window)
{
    for(int i=0;i<TOTAL_MENU_ITEMS;i++)
    {
        window.draw(m_menuItems[i]);
    }
    
}