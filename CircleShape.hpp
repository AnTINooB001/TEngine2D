#ifndef CIRCLE_OBJECT_H
#define CIRCLE_OBJECT_H

#include "Object.hpp"
#include <iostream>

class CircleObject : public Object
{
    sf::Texture texture;
public:
    CircleObject(Object*,std::string,float r, sf::Vector2f pos_ = sf::Vector2f(0,0));
    int loadTexture(std::string);
    void draw(sf::RenderWindow&);
    virtual ~CircleObject();
};

#endif