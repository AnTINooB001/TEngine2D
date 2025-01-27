#include "RectangleObject.hpp"

RectangleObject::RectangleObject(RectangleObject* fatherObject_,sf::Vector2f sz_, sf::Vector2f pos_) : fatherObject{fatherObject_}, sz{sz_}, pos{pos_}
{
    
    shape = sf::RectangleShape(sz);
    shape.setPosition(pos);
    std::cout<<"created object\n";
}

int RectangleObject::loadTexture(std::string path)
{
    if(!texture.loadFromFile(path))
    {
        std::cout<<"cant load texture from path " << path << "\n";
        return -1;
    }
    shape.setTexture(&texture);
    return 1;
}

void RectangleObject::setFather(RectangleObject* fatherObject_)
{
    fatherObject = fatherObject_;
}

RectangleObject* RectangleObject::getFather()
{
    return fatherObject;
}

void RectangleObject::move(sf::Vector2f dPos_)
{
    setPosition(pos+dPos_);
}

void RectangleObject::setPosition(sf::Vector2f pos_)
{
    pos = pos_;
    if(fatherObject)
        shape.setPosition(getGlobalPosition());
    else
        shape.setPosition(pos);
}

sf::Vector2f RectangleObject::getPosition() const
{
    return pos;
}

sf::Vector2f RectangleObject::getGlobalPosition() const
{
    if(fatherObject)
        return pos+fatherObject->getGlobalPosition();
    return pos;
}

void RectangleObject::setSize(sf::Vector2f sz_)
{
    sz = sz_;
}

sf::Vector2f RectangleObject::getSize() const
{
    return sz;
}

void RectangleObject::draw(sf::RenderWindow& window)
{
    setPosition(pos);
    window.draw(shape);
}

