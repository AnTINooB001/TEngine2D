#include "Camera.hpp"

Camera::Camera(World* world_,RectangleObject* father,sf::Vector2f sz_, sf::Vector2f pos_) : RectangleObject(father,sz_,pos_), world{world_}
{
    std::cout<<"created camera\n";
}

void Camera::move(sf::Vector2f dPos)
{
    //RectangleObject::move(-dPos);
    pos += dPos;
    world->move(dPos);
}