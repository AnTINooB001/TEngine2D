#include "RectangleObject.hpp"

RectangleObject::RectangleObject(Object* fatherObject_,std::string name_,sf::Vector2f sz_, sf::Vector2f pos_) : Object{fatherObject_,name_,sz_,pos_}
{
    shape = new sf::RectangleShape(sz);
    shape->setPosition(pos);
    std::cout<<"created rectangle\n";
}

int RectangleObject::loadTexture(std::string path)
{
    if(!texture.loadFromFile(path))
    {
        std::cout<<"cant load texture from path " << path << "\n";
        return -1;
    }
    shape->setTexture(&texture);
    return 1;
}

void RectangleObject::draw(sf::RenderWindow& window)
{
    window.draw(*shape);
}

RectangleObject::~RectangleObject()
{
    delete shape;
}