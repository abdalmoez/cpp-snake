#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "util/iterable_queue.hpp"
#include "Constants.h"
#include "Globals.h"

class Snake 
{

    public:
        Snake(int grid_width, int grid_height, int scale=32);

        void render(sf::RenderWindow& window);

        void update();

        void onKeyPress(sf::Event& event);
        void up();
        void down();
        void left();
        void right();
        void Init();
        
        void generateRandomFoodPosition();
        sf::Vector2f& getNextStepCoord();
        bool isCrashed();
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
#endif