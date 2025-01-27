#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "RectangleObject.hpp"

class Player : public RectangleObject
{
public:
    Player(RectangleObject*,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));
};

#endif