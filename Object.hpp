#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define EXIT_SUCCESSFUL 1
#define EXIT_BAD -1


class Object
{

protected:  
    std::string name;
    sf::Shape* shape;
    Object* fatherObject;
    sf::Vector2f pos;       // position relative to object
    sf::Vector2f sz;
    bool drawable = true;
public:
    Object(Object*,std::string,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));
    virtual void setFather(Object*);
    virtual Object* getFather();
    virtual sf::Vector2f getPosition() const;
    virtual sf::Vector2f getGlobalPosition() const; // position relative to world
    virtual void setSize(sf::Vector2f);
    virtual sf::Vector2f getSize() const;
    virtual void rotate(int angle);
    virtual ~Object();
    virtual void move(sf::Vector2f);
    virtual void setPosition(sf::Vector2f);
    virtual void setDrawable(bool);
    virtual bool isDrawable() const;
    virtual bool isCollisioned(Object*);
    virtual void draw(sf::RenderWindow&) = 0;
    virtual int loadTexture(std::string) = 0;
    virtual std::string getName() const;
    virtual void setName(std::string);
    sf::FloatRect getGlobalBounds() const;
};



#endif