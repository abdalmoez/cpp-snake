#include "Snake.h"
#include <iostream>

Snake::Snake(int grid_width, int grid_height, int scale):
 m_position(grid_width/2,grid_height/2)
,m_orientation(1.0f,0.0f)
,m_orientationChanged(false)
,m_foodPosition()
,m_queue()
,m_speed(400)//Default 50
,m_gridWidth(grid_width)
,m_gridHeight(grid_height)
,m_screenScale(scale)
,m_clock()// starts the clock
{}

void Snake::render(sf::RenderWindow& window)
{
    if(m_clock.getElapsedTime().asMilliseconds()>=std::max(50,500 - m_speed))
    {
        m_clock.restart();
        update();
    }
    sf::RectangleShape shape(sf::Vector2f(m_screenScale, m_screenScale));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(GRID_SCALE*m_foodPosition.x, GRID_SCALE*m_foodPosition.y);
    window.draw(shape);
    for(auto it=m_queue.begin(); it!=m_queue.end();++it)
    {
        shape.setPosition(GRID_SCALE* ((*it)->x), GRID_SCALE*((*it)->y));
        shape.setFillColor(sf::Color(0xFFE1D9C9));
        window.draw(shape);        
    }
    shape.setFillColor(sf::Color(0xFF725a48));
    shape.setPosition(GRID_SCALE*m_position.x, GRID_SCALE*m_position.y);
    window.draw(shape);
    if(isCrashed())
    {
        game_state=GAME_STATE_MENU_GAMEOVER;
        lastscore = m_queue.size() - 2;
        if(lastscore>highscore)
        {
            highscore=lastscore;
        }
    }
}
sf::Vector2f& Snake::getNextStepCoord()
{
    sf::Vector2f* v = new sf::Vector2f(m_position.x + m_orientation.x, m_position.y + m_orientation.y);
    if(v->x < 0)
    {
        v->x += m_gridWidth;
    }
    if(v->x >= m_gridWidth)
    {
        v->x -= m_gridWidth;
    }            
    
    if(v->y < 0)
    {
        v->y += m_gridHeight;
    }
    if(v->y >= m_gridHeight)
    {
        v->y -= m_gridHeight;
    }
    return *v;
}
void Snake::update()
{
    m_queue.push(new sf::Vector2f(m_position.x, m_position.y));

    m_position = getNextStepCoord();
    m_orientationChanged = false;

    bool food_was_found = m_position == m_foodPosition;

    if(food_was_found)
    {
        generateRandomFoodPosition();
        //m_speed+=50;
    }
    else
    {
        m_queue.pop();
    }
}

void Snake::onKeyPress(sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Up:      up(); break;
        case sf::Keyboard::Down:    down(); break;
        case sf::Keyboard::Left:    left(); break;
        case sf::Keyboard::Right:   right(); break;
    }
}
void Snake::up()
{ 
    if(m_orientation.y == 0 && !m_orientationChanged)
    { 
        m_orientation.x= 0;
        m_orientation.y=-1;
        m_orientationChanged = true;
    } 
}
void Snake::down()
{ 
    if(m_orientation.y == 0 && !m_orientationChanged)
    { 
        m_orientation.x= 0;
        m_orientation.y= 1;
        m_orientationChanged = true;
    }
}
void Snake::left()
{ 
    if(m_orientation.x == 0 && !m_orientationChanged)
    { 
        m_orientation.x=-1;
        m_orientation.y= 0;
        m_orientationChanged = true;
    }
}
void Snake::right()
{ 
    if(m_orientation.x == 0 && !m_orientationChanged)
    { 
        m_orientation.x= 1;
        m_orientation.y= 0;
        m_orientationChanged = true;
    }
}

void Snake::generateRandomFoodPosition()
{
    m_foodPosition.x = std::rand() % m_gridWidth;
    m_foodPosition.y = std::rand() % m_gridHeight;
}

bool Snake::isCrashed()
{
    for(auto it=m_queue.begin(); it!=m_queue.end();++it)
    {
        if(**it == m_position)
            return true;        
    }
    return false;
}

void Snake::Init()
{

    generateRandomFoodPosition();
    m_position.x = (float)(m_gridWidth / 2);
    m_position.y = (float)(m_gridHeight / 2);
    m_orientation.x = 1;
    m_orientation.y = 0;
    m_speed = 50;
    m_queue.clear();
    m_queue.push(new sf::Vector2f(m_position.x - 2.0f, m_position.y));
    m_queue.push(new sf::Vector2f(m_position.x - 1.0f, m_position.y));
}