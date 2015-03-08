#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../headers/snake.h"
#include "../headers/apple.h"

using namespace std;

int main()
{
    srand(time(NULL));
    sf::Time cooldown;
    cooldown = sf::seconds( 0.1f );
    sf::Clock frameclock;
    sf::Time elapsedtime;
    sf::RenderWindow window(sf::VideoMode(800,600), "Flappy Me!"); // tworzenie glownego okna
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    int key = rand() % 4 + 1;
    Apple apple;
    apple.load_files();
    apple.rand_position();
    Snake snake;
    if (snake.load_files() == false)
        return -1;
    sf::Texture background;
    if (!background.loadFromFile("img/background.png"))
        return -1;
    sf::Sprite background_sprite; // sprite tla
    background_sprite.setTexture(background);
    background_sprite.setPosition(0,0); // ustawianie spritow
    while (window.isOpen()) // glowna petla
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                key = 1;
                cout << snake.x << endl << snake.y << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                key = 2;
                cout << snake.x << endl << snake.y << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                key = 3;
                cout << snake.x << endl << snake.y << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                key = 4;
                cout << snake.x << endl << snake.y << endl;
            }

        }
        elapsedtime += frameclock.restart();
        if( elapsedtime >= cooldown )
        {
            elapsedtime = sf::Time::Zero;
            snake.move_snake(key);
        }
        if(snake.check_collision(apple))
        {
            snake.length+=1;
            do{
                apple.rand_position();
            } while (snake.check_collision_body(apple));

        }
        if(snake.check_head_collision())
        {
            snake.speed = 1;

        }
        window.clear(); // czyszczenie okna
        window.draw(apple.apple);
        snake.draw(window);
        //window.draw(background_sprite);
        //window.draw(snake.head);
        window.display();
    }

    return 0;
}
