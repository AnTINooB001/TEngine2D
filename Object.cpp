#include "Object.hpp"

Object::Object(Object* fatherObject_,std::string name_,sf::Vector2f sz_, sf::Vector2f pos_) : fatherObject{fatherObject_},name{name_}, sz{sz_}, pos{pos_}
{
    std::cout<<"created object\n";
}

void Object::setFather(Object* fatherObject_)
{
    fatherObject = fatherObject_;
}

Object* Object::getFather()
{
    return fatherObject;
}

void Object::move(sf::Vector2f dPos_)
{
    setPosition(pos+dPos_);
}

void Object::setPosition(sf::Vector2f pos_)
{
    pos = pos_;
    shape->setPosition(pos);
}

sf::Vector2f Object::getPosition() const
{
    return pos;
}

sf::Vector2f Object::getGlobalPosition() const
{
    if(fatherObject)
        return pos+fatherObject->getGlobalPosition();
    return pos;
}

void Object::setSize(sf::Vector2f sz_)
{
    sz = sz_;
}

sf::Vector2f Object::getSize() const
{
    return sz;
}

void Object::rotate(int angle)
{
    
}

bool Object::isDrawable() const
{
    return drawable;
}

void Object::setDrawable(bool value)
{
    drawable = value;
}

void Object::setName(std::string name_)
{
    name = name_;
}

std::string Object::getName() const 
{
    return name;
}

bool Object::isCollisioned(Object* obj)
{
    return shape->getGlobalBounds().intersects(obj->shape->getGlobalBounds());
}

sf::FloatRect Object::getGlobalBounds() const
{
    return shape->getGlobalBounds();
}

Object::~Object()
{}