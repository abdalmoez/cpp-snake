#ifndef UTIL_SFML_ADDON_H
#define UTIL_SFML_ADDON_H

#include <SFML/Graphics.hpp>
#include "../Constants.h"

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);

sf::RectangleShape* createCube(int x, int y, sf::Color color);

sf::Font& getDefaultFont();

#endif