#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.hpp"
#include "Camera.hpp"
#include "CircleShape.hpp"
#include "Player.hpp"



#define CAM_BORDER 70

#define CAM_HEIGHT 600
#define CAM_WIDTH 900

#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 50

#define ENEMY_HEIGHT 50
#define ENEMY_WIDTH 50
sf::Vector2f enemyPos(30,30);

float playerSpeed = 0.1f;
sf::Vector2f pos_off(0,0);

void processPlayerMove(World*,Camera*, Player*);    


struct Keys
{
    sf::Keyboard::Key moveLeft = sf::Keyboard::A;
    sf::Keyboard::Key moveRight = sf::Keyboard::D;
    sf::Keyboard::Key moveUp = sf::Keyboard::W;
    sf::Keyboard::Key moveDown = sf::Keyboard::S;
    sf::Keyboard::Key fire = sf::Keyboard::E;
    sf::Mouse::Button navigate = sf::Mouse::Right;
    sf::Mouse::Button click = sf::Mouse::Left;
    
} Key;



int main(int argc, char* argv[])            
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(CAM_WIDTH,CAM_HEIGHT), "Game");

    World* world = World::getWorld(sf::Vector2f(5000,5000),"map.png");
    if(world == nullptr)
    {
        std::cout<<"world is nullptr!" << "\n";
        return -1;
    }
    Camera* camera = new Camera{world,nullptr,sf::Vector2f(CAM_WIDTH,CAM_HEIGHT)};
    Player* player = new Player{nullptr,sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT),sf::Vector2f(CAM_WIDTH/2,CAM_HEIGHT/2)};
    //player->loadTexture("map.png");
    world->addObject(player);
    if(player == nullptr || camera == nullptr)
    {
        std::cout<<"player or camera is nullptr!" << "\n";
        return -1;
    }

    CircleObject c{nullptr,"circle",30, enemyPos+enemyPos+enemyPos+enemyPos+enemyPos};
    world->addObject(&c);

    RectangleObject enemy{nullptr,"enemy",sf::Vector2f{ENEMY_WIDTH,ENEMY_HEIGHT}, enemyPos};
    world->addObject(&enemy);
    //enemy.setDrawable(false);
    RectangleObject enemy2{&enemy,"enemy2",sf::Vector2f{ENEMY_WIDTH,ENEMY_HEIGHT}, enemyPos};
    world->addObject(&enemy2);

    RectangleObject stone{nullptr,"stone",sf::Vector2f{ENEMY_WIDTH,ENEMY_HEIGHT}, enemyPos};
    world->addObject(&stone); 

    
    sf::Vector2i prev_mouse_pos(0,0);
    bool pressed = false;
    sf::Event ev;
    while(window.isOpen())
    {
        
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
                window.close();
            if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Button::Right)
            {
                pressed = true;
                prev_mouse_pos = sf::Mouse::getPosition();
            }
                
            else if(ev.type == sf::Event::MouseButtonReleased)
                pressed = false;
            if(ev.type == sf::Event::MouseMoved && pressed)
            {
                auto curr_mouse_pos = sf::Mouse::getPosition();
                sf::Vector2f dPos;
                dPos.x = curr_mouse_pos.x-prev_mouse_pos.x;
                dPos.y = curr_mouse_pos.y-prev_mouse_pos.y;

                camera->move(-dPos);

                pos_off += dPos;
                prev_mouse_pos = curr_mouse_pos;
            }
            if(ev.type == sf::Event::KeyPressed)
            {
                camera->move(pos_off);
                pos_off.x = 0;
                pos_off.y = 0;
            }
            
        }

        enemy.move(sf::Vector2f(0.01,0.01));
        //enemy2.move(sf::Vector2f(0.01,0.01));
        // ---------------------------------- KEYBOARD ----------------------------------------------------

        processPlayerMove(world,camera,player);

        // -------------------------   z ------------------------------------------------

        window.clear();
        world->draw(window);
        window.display();                   
        //std::cout<<"player position x - " << player->getPosition().x << " y - " << player->getPosition().y << "\n";
        std::cout<<"player coord x - " << player->getGlobalBounds().getPosition().x << " y - " << player->getGlobalBounds().getPosition().y << "\n";
        // std::cout<<"enemy1 coord x - " << enemy.getGlobalPosition().x << " y - " << enemy.getGlobalPosition().y << "\n";
        //std::cout<<"enemy2 coord x - " << enemy2.getGlobalBounds().getPosition().x << " y - " << enemy2.getGlobalBounds().getPosition().y << "\n";
        //std::cout<<"stone coord x - " << stone.getGlobalPosition().x << " y - " << stone.getGlobalPosition().y << "\n";
        //std::cout<<"world position x - " << world->getPosition().x << " y - " << world->getPosition().y << "\n";
        std::cout<<"camera coords x - " << camera->getPosition().x << " y - " << camera->getPosition().y << "\n";
    }
    
    return 0;
}


void processPlayerMove(World* world,Camera* camera, Player* player)
{
    for(auto& el : World::getWorld()->getObjects()) {
        if(player->isCollisioned(el.second) && el.second->isDrawable() && el.second->getName() != player->getName() )
        {
            sf::Vector2f dist = el.second->getGlobalPosition() - player->getGlobalPosition();
            dist.x /= abs(dist.x);
            dist.y /= abs(dist.y);
            
            player->move(sf::Vector2f(-playerSpeed*dist.x,-playerSpeed*dist.y));
            break;
        }
    }
    if(sf::Keyboard::isKeyPressed(Key.moveDown))        
    {
        if(player->getGlobalPosition().y-camera->getGlobalPosition().y > camera->getSize().y-CAM_BORDER-player->getSize().y)
            camera->move(sf::Vector2f(0,playerSpeed));
        player->move(sf::Vector2f(0,playerSpeed));
    }
    if(sf::Keyboard::isKeyPressed(Key.moveUp))
    {
        if(player->getGlobalPosition().y-camera->getGlobalPosition().y < CAM_BORDER)
            camera->move(sf::Vector2f(0,-playerSpeed));
        player->move(sf::Vector2f(0,-playerSpeed));

    }
    if(sf::Keyboard::isKeyPressed(Key.moveLeft))
    {
        if(player->getGlobalPosition().x-camera->getGlobalPosition().x < CAM_BORDER)
            camera->move(sf::Vector2f(-playerSpeed,0));
        player->move(sf::Vector2f(-playerSpeed,0));
    }
    if(sf::Keyboard::isKeyPressed(Key.moveRight))
    {
        if(player->getGlobalPosition().x-camera->getGlobalPosition().x > CAM_WIDTH-CAM_BORDER-PLAYER_WIDTH)
            camera->move(sf::Vector2f(playerSpeed,0));
        player->move(sf::Vector2f(playerSpeed,0));
    }
    if(sf::Keyboard::isKeyPressed(Key.fire))
    {
        static int count = 0;
        
    }
} 