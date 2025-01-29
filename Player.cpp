#include "Player.hpp"

Player::Player(RectangleObject* father,sf::Vector2f sz_, sf::Vector2f pos_) : RectangleObject(father,"Player",sz_,pos_)
{   
    std::cout<<"created player\n";
}