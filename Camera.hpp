#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "RectangleObject.hpp"
#include "World.hpp"

class Camera : public RectangleObject
{
private:
    World* world;
public:
    Camera(World*,RectangleObject*,sf::Vector2f sz_, sf::Vector2f pos_ = sf::Vector2f(0,0));
    Camera() = delete;
    void move(sf::Vector2f) override;
};

#endif