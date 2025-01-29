#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"


class World
{
private:
    
    static inline World* wworld{nullptr};
    Map* map = nullptr;
    std::map<std::string,Object*> objects;
    World(sf::Vector2f,std::string, sf::Vector2f);
    void addObjectController(void(*controller()));
public:
    static World* getWorld(sf::Vector2f = sf::Vector2f(0,0),std::string = "");
    void addObject(Object*);
    void removeObjectByName(std::string);
    void removeObject(Object*);
    Object* getObjectByName(std::string);
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f dPos);
    sf::Vector2f getPosition() const;
    std::map<std::string,Object*> getObjects() const;
    
    ~World();
};


#endif