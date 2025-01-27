#ifndef MAP_HPP
#define MAP_HPP

#include "RectangleObject.hpp"

class Map : public RectangleObject
{
public:
    Map(RectangleObject*,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));

};

#endif