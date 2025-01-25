#ifndef PLAYER_H
#define PLAYER_H

//#include "Object.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class RectangleObject
{
private:
    sf::RectangleShape shape;
    RectangleObject* fatherObject;
    sf::Texture texture;
    sf::Vector2f pos;
    sf::Vector2f sz;
public:
    RectangleObject(RectangleObject*,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));
    int loadTexture(std::string);
    void setFather(RectangleObject*);
    RectangleObject* getFather();
    void move(sf::Vector2f);
    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition() const;
    sf::Vector2f getCoord() const;
    void setSize(sf::Vector2f);
    sf::Vector2f getSize() const;
    void draw(sf::RenderWindow&);
 
};

#endif