#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>
#include <queue>
#include <deque>
#include "Globals.h"

//GameState game_state = GAME_STATE_MAIN_MENU;

template<typename T, typename Container=std::deque<T> >
class iterable_queue : public std::queue<T,Container>
{
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}

sf::RectangleShape* createCube(int x, int y, sf::Color color)
{
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(SCALE,SCALE));
    shape->setFillColor(color);
    shape->setPosition(SCALE*x, SCALE*y);
    return shape;
}

class Snake 
{

    public:
        Snake(int grid_width, int grid_height, int scale=32):
         m_position(grid_width/2,grid_height/2)
        ,m_orientation(1,0)
        ,m_foodPosition()
        ,m_queue()
        ,m_speed(50)
        ,m_gridWidth(grid_width)
        ,m_gridHeight(grid_height)
        ,m_screenScale(scale)
        ,m_clock()// starts the clock
        {
            generateRandomFoodPosition();
            m_queue.push(new sf::Vector2f(grid_width/2 -2, grid_height/2));
            m_queue.push(new sf::Vector2f(grid_width/2 -1, grid_height/2));
        }

        void render(sf::RenderWindow& window)
        {
            if(m_clock.getElapsedTime().asMilliseconds()>=std::max(50,500 - m_speed))
            {
                m_clock.restart();
                update();
            }

            sf::RectangleShape shape(sf::Vector2f(m_screenScale, m_screenScale));
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(SCALE*m_foodPosition.x, SCALE*m_foodPosition.y);
            window.draw(shape);
            for(auto it=m_queue.begin(); it!=m_queue.end();++it)
            {
                shape.setPosition(SCALE* ((*it)->x), SCALE*((*it)->y));
                shape.setFillColor(sf::Color(0xFFE1D9C9));
                window.draw(shape);        
            }
            shape.setFillColor(sf::Color(0xFF725a48));
            shape.setPosition(SCALE*m_position.x, SCALE*m_position.y);
            window.draw(shape);
        }

        void update()
        {
            m_queue.push(new sf::Vector2f(m_position.x, m_position.y));


            m_position.x = m_position.x + m_orientation.x;
            if(m_position.x < 0)
            {
                m_position.x += m_gridWidth;
            }
            if(m_position.x >= m_gridWidth)
            {
                m_position.x -= m_gridWidth;
            }            
            
            m_position.y = m_position.y + m_orientation.y;
            if(m_position.y < 0)
            {
                m_position.y += m_gridHeight;
            }
            if(m_position.y >= m_gridHeight)
            {
                m_position.y -= m_gridHeight;
            }

            bool food_was_found = m_position == m_foodPosition;

            if(food_was_found)
            {
                generateRandomFoodPosition();
                m_speed+=50;
            }
            else
            {
                m_queue.pop();
            }
        }

        void onKeyPress(sf::Event& event)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:      up(); break;
                case sf::Keyboard::Down:    down(); break;
                case sf::Keyboard::Left:    left(); break;
                case sf::Keyboard::Right:   right(); break;
            }
        }
        void up()       { if(m_orientation.y == 0)  { m_orientation.x= 0; m_orientation.y=-1; } }
        void down()     { if(m_orientation.y == 0)  { m_orientation.x= 0; m_orientation.y= 1; } }
        void left()     { if(m_orientation.x == 0)  { m_orientation.x=-1; m_orientation.y= 0; } }
        void right()    { if(m_orientation.x == 0)  { m_orientation.x= 1; m_orientation.y= 0; } }
        
        void generateRandomFoodPosition()
        {
            m_foodPosition.x = std::rand() % m_gridWidth;
            m_foodPosition.y = std::rand() % m_gridHeight;
        }
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_orientation;        
        sf::Vector2f m_foodPosition;
        iterable_queue<sf::Vector2f*> m_queue;
        int m_speed;
        const int m_gridWidth;
        const int m_gridHeight;
        const int m_screenScale;
        sf::Clock m_clock; 
};



int main()
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(50);
    sf::View view;
    view.setSize( WIDTH, HEIGHT );
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );
    view = getLetterboxView( view, WIDTH, HEIGHT );  

    
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
                    break;
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
                        case GAME_STATE_INGAME:     snake.onKeyPress(event);      break;
                        case GAME_STATE_MAIN_MENU:  mainMenu.onKeyPressed(event); break;
                    }
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    switch (game_state)
                    {
                        case GAME_STATE_MAIN_MENU:  mainMenu.onMouseMove(event); break;
                    }
                    break;
                } 
                case sf::Event::MouseButtonPressed:
                {
                    switch (game_state)
                    {
                        case GAME_STATE_MAIN_MENU:  mainMenu.onMouseClick(event); break;
                    }                    
                    break;
                } 
            }
        }
        
        window.clear();
        window.setView(view); 
        
        switch (game_state)
        {
            case GAME_STATE_INGAME:     snake.render(window);    break;
            case GAME_STATE_MAIN_MENU:  mainMenu.render(window); break;
        }
        window.display();
    }

    return 0;
}