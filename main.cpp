#include <SFML/Graphics.hpp>
#include <iostream>
#include "RectangleObject.hpp"

#define EXIT_SUCCESSFUL 1


#define CAM_BORDER 70

#define CAM_HEIGHT 600
#define CAM_WIDTH 900

#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 50

#define ENEMY_HEIGHT 50
#define ENEMY_WIDTH 50
sf::Vector2f enemyPos(30,30);

float playerSpeed = 0.3f; 
sf::Vector2f pos_off(0,0);

void processPlayerMove(RectangleObject&,RectangleObject&, RectangleObject&);    
void returnCamToPlayer(RectangleObject&,RectangleObject&,sf::Vector2f&);
void moveCamera(RectangleObject& world, RectangleObject& player,RectangleObject& camera, sf::Vector2f dPos);

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

    RectangleObject world{nullptr,sf::Vector2f(5000,5000)};         
    if(world.loadTexture("map.png") != EXIT_SUCCESSFUL)
        return -1;

    RectangleObject camera{nullptr,sf::Vector2f(CAM_WIDTH,CAM_HEIGHT)};

    RectangleObject player{&camera,sf::Vector2f{PLAYER_WIDTH,PLAYER_HEIGHT},sf::Vector2f{CAM_WIDTH/2-PLAYER_WIDTH/2,CAM_HEIGHT/2-PLAYER_HEIGHT/2}};
    if(player.loadTexture("map.png") != EXIT_SUCCESSFUL)
        return -1;

    RectangleObject enemy{&world,sf::Vector2f{ENEMY_WIDTH,ENEMY_HEIGHT}, enemyPos};
    // if(enemy.loadTexture("map.png") != EXIT_SUCCESSFUL)
    //     return -1;       

    int cd = 1;
    int bullet_count = 10;
    sf::Vector2f bulletSz(3,3);
    std::vector<RectangleObject> bullets;
    RectangleObject bullet(&player,bulletSz);
    // for (size_t i = 0; i < bullet_count; i++)
    // {
    //     RectangleObject bullet(&player,bulletSz);
    //     bullets.push_back(bullet);
    // }
    
    
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

                moveCamera(world,player,camera,dPos);

                pos_off += dPos;
                prev_mouse_pos = curr_mouse_pos;
            }
            if(ev.type == sf::Event::KeyPressed)
            {
                moveCamera(world,player,camera,-pos_off);
                pos_off.x = 0;
                pos_off.y = 0;
            }
            
        }

        // ---------------------------------- KEYBOARD ----------------------------------------------------
        enemy.move(sf::Vector2f(rand()%10 * 1.f / 100 + rand()%10 * 1.f / 100,rand()%10 * 1.f / 100 + rand()%10 * 1.f / 100));

        processPlayerMove(world,camera,player);

        // -------------------------    ------------------------------------------------

        window.clear();
        world.draw(window);
        player.draw(window);
        enemy.draw(window);
        window.display();
    
    }

    return 0;
}

void moveCamera(RectangleObject& world, RectangleObject& player,RectangleObject& camera, sf::Vector2f dPos)
{
    world.setPosition(world.getPosition()+dPos);
    player.setPosition(player.getPosition()+dPos);
}

void processPlayerMove(RectangleObject& world,RectangleObject& camera, RectangleObject& player)
{
    
    if(sf::Keyboard::isKeyPressed(Key.moveDown))
    {
        if(player.getPosition().y > camera.getSize().y-CAM_BORDER-player.getSize().y)
            world.move(sf::Vector2f(0,-playerSpeed));
        else
            player.move(sf::Vector2f(0,playerSpeed));
            
    }
    if(sf::Keyboard::isKeyPressed(Key.moveUp))
    {
        if(player.getPosition().y < CAM_BORDER)
            world.move(sf::Vector2f(0,playerSpeed));
        else
            player.move(sf::Vector2f(0,-playerSpeed));
    }
    if(sf::Keyboard::isKeyPressed(Key.moveLeft))
    {
        if(player.getPosition().x < CAM_BORDER)
            world.move(sf::Vector2f(playerSpeed,0));
        else
            player.move(sf::Vector2f(-playerSpeed,0));
    }
    if(sf::Keyboard::isKeyPressed(Key.moveRight))
    {
        if(player.getPosition().x > CAM_WIDTH-CAM_BORDER-PLAYER_WIDTH)
            world.move(sf::Vector2f(-playerSpeed,0));
        else
            player.move(sf::Vector2f(playerSpeed,0));
    }
    if(sf::Keyboard::isKeyPressed(Key.fire))
    {
        static int count = 0;
        
    }
}