#ifndef WORLD_HPP
#define WORLD_HPP

#include "Player.hpp"
#include "Map.hpp"


class World
{
private:
    static inline World* wworld{nullptr};
    Player* player = nullptr;
    Map* map = nullptr;
    std::map<std::string,RectangleObject*> objects;     
    sf::Vector2f size;
    sf::Vector2f position;
    World(sf::Vector2f,std::string, sf::Vector2f);
    void addObjectController(void(*controller()));
public:
    static World* createWorld(sf::Vector2f,std::string);
    void addObject(RectangleObject*,std::string);
    void removeObjectByName(std::string);
    void removeObject(RectangleObject*);
    RectangleObject* getObjectByName(std::string);
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f dPos);
    sf::Vector2f getPosition() const;
    
    ~World();
};


#endif