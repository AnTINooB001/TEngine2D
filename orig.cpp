#include <SFML/Graphics.hpp>
#include <iostream>

#define CAM_BORDER 70

#define CAM_HEIGHT 400
#define CAM_WIDTH 600
sf::Vector2f worldPos(0,0);

#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 50
sf::Vector2f playerPos(CAM_WIDTH/2-PLAYER_WIDTH/2,CAM_HEIGHT/2-PLAYER_HEIGHT/2);

#define ENEMY_HEIGHT 50
#define ENEMY_WIDTH 50
sf::Vector2f enemyPos(30,30);

double playerSpeed = 0.1f; 

struct Keys
{
    sf::Keyboard::Key moveLeft = sf::Keyboard::A;
    sf::Keyboard::Key moveRight = sf::Keyboard::D;
    sf::Keyboard::Key moveUp = sf::Keyboard::W;
    sf::Keyboard::Key moveDown = sf::Keyboard::S;
    sf::Mouse::Button navigate = sf::Mouse::Right;
    sf::Mouse::Button click = sf::Mouse::Left;
} Key;

int main(int argc, char* argv[])            
{
    sf::RenderWindow window(sf::VideoMode(CAM_WIDTH,CAM_HEIGHT), "Game");

    sf::RectangleShape word(sf::Vector2f(5000,5000));
    sf::Texture mapTexture;
    if(!mapTexture.loadFromFile("map.png"))
    {
        std::cout<<"Cant find map texture!\n";
        return -1;
    }
    word.setTexture(&mapTexture);

    sf::RectangleShape player(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("map.png"))
    {
        std::cout<<"Cant find map texture!\n";
        return -1;
    }
    //player.setTexture(&playerTexture);

    sf::RectangleShape enemy(sf::Vector2f(ENEMY_WIDTH,ENEMY_HEIGHT));
    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("map.png"))
    {
        std::cout<<"Cant find map texture!\n";
        return -1;
    }
    //enemy.setTexture(&playerTexture);
    int x_off = 0;
    int y_off = 0;
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
                int dx = curr_mouse_pos.x-prev_mouse_pos.x;
                int dy = curr_mouse_pos.y-prev_mouse_pos.y;
                prev_mouse_pos = curr_mouse_pos;
                
                x_off += dx;
                y_off += dy;
                worldPos.x += dx;
                worldPos.y += dy;
                playerPos.x += dx;
                playerPos.y += dy;
            }
        }

        // ---------------------------------- KEYBOARD ----------------------------------------------------

        if(sf::Keyboard::isKeyPressed(Key.moveDown))
        {
            worldPos.x -= x_off;
            worldPos.y -= y_off;
            playerPos.x -= x_off;
            playerPos.y -= y_off;
            x_off = 0;
            y_off = 0;

            if(playerPos.y > CAM_HEIGHT-CAM_BORDER-PLAYER_HEIGHT)
                worldPos.y -= playerSpeed;
            else
                playerPos.y += playerSpeed;
                
        }
        if(sf::Keyboard::isKeyPressed(Key.moveUp))
        {
            worldPos.x -= x_off;
            worldPos.y -= y_off;
            playerPos.x -= x_off;
            playerPos.y -= y_off;
            x_off = 0;
            y_off = 0;

            if(playerPos.y < CAM_BORDER)
                worldPos.y += playerSpeed;
            else
                playerPos.y -= playerSpeed;
        }
        if(sf::Keyboard::isKeyPressed(Key.moveLeft))
        {
            worldPos.x -= x_off;
            worldPos.y -= y_off;
            playerPos.x -= x_off;
            playerPos.y -= y_off;
            x_off = 0;
            y_off = 0;

            if(playerPos.x < CAM_BORDER)
                worldPos.x += playerSpeed;
            else
                playerPos.x -= playerSpeed;
        }
        if(sf::Keyboard::isKeyPressed(Key.moveRight))
        {
            worldPos.x -= x_off;
            worldPos.y -= y_off;
            playerPos.x -= x_off;
            playerPos.y -= y_off;
            x_off = 0;
            y_off = 0;

            if(playerPos.x > CAM_WIDTH-CAM_BORDER-PLAYER_WIDTH)
                worldPos.x -= playerSpeed;
            else
                playerPos.x += playerSpeed;
        }

        // -------------------------------------------------------------------------

        
    
        player.setPosition(playerPos);
        word.setPosition(worldPos);
        enemy.setPosition(worldPos.x + enemyPos.x,worldPos.y + enemyPos.y);

        window.clear();
        window.draw(word);
        window.draw(player);
        window.draw(enemy);
        window.display();
    
    }

    return 0;
}

