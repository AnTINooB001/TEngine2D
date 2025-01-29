#include "Map.hpp"

Map::Map(RectangleObject* father,sf::Vector2f sz_, sf::Vector2f pos_) : RectangleObject(father,"Map",sz_,pos_)
{
    std::cout<<"map created\n";
}