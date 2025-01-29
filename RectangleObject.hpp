#ifndef RECTANGLE_OBJECT_H
#define RECTANGLE_OBJECT_H

#include "Object.hpp"
#include <iostream>

class RectangleObject : public Object
{
    sf::Texture texture;
public:
    RectangleObject(Object*,std::string,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));
    int loadTexture(std::string);
    void draw(sf::RenderWindow&);
    virtual ~RectangleObject();
};

#endif