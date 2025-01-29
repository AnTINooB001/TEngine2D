#include "CircleShape.hpp"

CircleObject::CircleObject(Object* fatherObject_,std::string name_,float r, sf::Vector2f pos_) : Object{fatherObject_,name_,sf::Vector2f{r,r},pos_}
{
    shape = new sf::CircleShape(r);
    shape->setPosition(pos);
    std::cout<<"created circle\n";
}

int CircleObject::loadTexture(std::string path)
{
    if(!texture.loadFromFile(path))
    {
        std::cout<<"cant load texture from path " << path << "\n";
        return -1;
    }
    shape->setTexture(&texture);
    return 1;
}

void CircleObject::draw(sf::RenderWindow& window)
{
    window.draw(*shape);
}

CircleObject::~CircleObject()
{
    delete shape;
}