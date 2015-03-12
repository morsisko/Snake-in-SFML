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
    //declaring time variables
    sf::Time cooldown;
    sf::Time points_cooldown;
    sf::Time elapsedtime;
    sf::Time elapsed_points_time;
    //setting time variables
    cooldown = sf::seconds( 0.1f );
    points_cooldown = sf::seconds ( 0.25f );
    //declaring clock variables
    sf::Clock frameclock;
    sf::Clock points_clock;
    //declaring text variables
    sf::Font font;
    sf::Text points;
    sf::Text score_to_get_text;
    sf::Text score_text;
    sf::Text error;
    //declaring background
    sf::Texture background;
    sf::Sprite background_sprite;
    //creating apple and snake
    Apple apple;
    Snake snake;
    //loading files
    if (!font.loadFromFile("fonts/angrybirds-regular.ttf"))
        return -1;
    if (snake.load_files() == false)
        return -1;
    if (apple.load_files() == false)
        return -1;
    if (!background.loadFromFile("img/background.png"))
        return -1;
    //creating and setting window
    sf::RenderWindow window(sf::VideoMode(1000,600), "Flappy Me!"); // tworzenie glownego okna
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    //setting apple position
    apple.rand_position();
    //setting background
    background_sprite.setTexture(background);
    background_sprite.setPosition(0,0);
    //setting text variales
    points.setFont(font);
    points.setPosition(880,85);
    points.setCharacterSize(40);
    score_to_get_text.setFont(font);
    score_to_get_text.setPosition(880,135);
    score_to_get_text.setCharacterSize(40);
    score_text.setFont(font);
    score_text.setPosition(880,185);
    score_text.setCharacterSize(40);
    error.setFont(font);
    //dif
    int key = rand() % 4 + 1; // snake direction

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
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                key = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                key = 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                key = 4;
            }

        }
        elapsedtime += frameclock.restart();
        elapsed_points_time += points_clock.restart();
        if( elapsedtime >= cooldown )
        {
            elapsedtime = sf::Time::Zero;
            if(snake.check_head_collision())
            {
                snake.speed = 0;
            }
            else
            {
                snake.move_snake(key);
            }

            points.setString(snake.return_points(snake.length));
            score_to_get_text.setString(apple.return_points());
            score_text.setString(snake.return_points(snake.score));

        }
        if (elapsed_points_time >= points_cooldown && apple.score_to_get > 0)
        {
            elapsed_points_time = sf::Time::Zero;
            apple.score_to_get -= 1;
        }
        if(snake.check_collision(apple))
        {
            snake.length+=1;
            snake.get_point.play();
            snake.score += apple.score_to_get;
            apple.score_to_get = 100;
            do
            {
                apple.rand_position();
            }
            while (snake.check_collision_body(apple));

        }
        window.clear(); // czyszczenie okna
        window.draw(background_sprite);
        window.draw(points);
        window.draw(score_text);
        window.draw(score_to_get_text);
        window.draw(apple.apple);
        snake.draw(window);
        window.display();
    }

    return 0;
}
