#include "World.hpp"

World::World(sf::Vector2f size_,std::string path_, sf::Vector2f position_)
{
    std::cout<< "Creating world\n";
    map = new Map{nullptr,size_,position_};
    if(map->loadTexture(path_) == -1)
        std::cout<<"map texture was not loaded\n";  
    std::cout<<"world created!\n";
}

World::~World()
{
    delete map;
}

World* World::getWorld(sf::Vector2f size_,std::string path_)
{
    
    if(wworld != nullptr)
        return wworld;
    wworld = new World(size_,path_,sf::Vector2f(0,0));
    return wworld;
}

void World::addObject(Object* object)
{
    if(object->getFather() == nullptr)
        object->setFather(map);
    objects[object->getName()] = object;
}

void World::removeObjectByName(std::string name)
{
    objects.erase(name);
}

void World::removeObject(Object* object)
{
    auto it = std::find_if(objects.begin(), objects.end(),[&](std::pair<std::string,Object*> el) { return object->getName() == el.second->getName();});
    if(it != objects.end());
        objects.erase(it);
    
}

Object* World::getObjectByName(std::string name)
{
    return objects[name];
}

void World::draw(sf::RenderWindow& window)
{
    map->draw(window);
    for(auto& el : objects)
    {
        sf::Vector2f prev_pos = el.second->getPosition();
        el.second->setPosition(el.second->getGlobalPosition() + this->getPosition()); // normalize coordinates to cs
       
        if(el.second->isDrawable())
            el.second->draw(window);

        el.second->setPosition(prev_pos);
    }
}

void World::move(sf::Vector2f dPos)
{
    map->move(dPos);
}

sf::Vector2f World::getPosition() const
{
    return map->getPosition();
}

std::map<std::string,Object*> World::getObjects() const
{
    return objects;
}