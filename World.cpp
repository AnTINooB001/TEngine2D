#include "World.hpp"

World::World(sf::Vector2f size_,std::string path_, sf::Vector2f position_) : size{size_}, position{position_}
{
    map = new Map{nullptr,size,position};
    if(map->loadTexture(path_) == -1)
        std::cout<<"map texture was not loaded\n";  
    std::cout<<"world created!\n";
}

World::~World()
{
    delete map;
}

World* World::createWorld(sf::Vector2f size_,std::string path_)
{
    std::cout<< "Creating world\n";
    if(wworld != nullptr)
        return wworld;
    wworld = new World(size_,path_,sf::Vector2f(0,0));
    return wworld;
}

void World::addObject(RectangleObject* object, std::string name)
{
    if(object->getFather() == nullptr)
        object->setFather(map);
    objects[name] = object;
}

void World::removeObjectByName(std::string name)
{
    objects.erase(name);
}

void World::removeObject(RectangleObject* object)
{
    auto it = std::find_if(objects.begin(), objects.end(),[&](std::pair<std::string,RectangleObject*> el) { return object == el.second;});
    if(it != objects.end());
        objects.erase(it);
    
}

RectangleObject* World::getObjectByName(std::string name)
{
    return objects[name];
}

void World::draw(sf::RenderWindow& window)
{
    map->draw(window);
    for(auto& el : objects)
    {
        el.second->draw(window);
        //std::cout<<"drawed - " << el.first << "\n";
    }
}

void World::move(sf::Vector2f dPos)
{
    position += dPos;
    map->move(-dPos);
}

sf::Vector2f World::getPosition() const
{
    return sf::Vector2f(0,0);
}