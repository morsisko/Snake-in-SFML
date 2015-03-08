#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../headers/snake.h"
#include "../headers/apple.h"
using namespace std;
bool Snake::load_files()
{
    if (!head_texture.loadFromFile("img/head.png"))
        return false;

    head.setTexture(head_texture);

    if (!body_texture.loadFromFile("img/part.png"))
        return false;

    body.setTexture(body_texture);

    position[0].x = x;
    position[0].y = y;
    return true;
}

void Snake::move_snake(int key)
{
    //  W
    //A S D

    //  1
    //2 3 4
    position[0].x = x;
    position[0].y = y;
    switch (key)
    {
    case 1:
        y-=speed;
        break;
    case 2:
        x-=speed;
        break;
    case 3:
        y+=speed;
        break;
    case 4:
        x+=speed;
        break;
    }
    head.setPosition(x,y);
    for (int i = length - 1; i != 0 ; i--)
    {
        position[i] = position[i-1];
    }
}

void Snake::draw(sf::RenderWindow &window)
{

    window.draw(head);
    for (int i = length - 1; i != 0 ; i--)
    {
        body.setPosition(position[i].x, position[i].y);
        window.draw(body);
    }
}

bool Snake::check_collision(Apple &apple)
{
    if (((y <= apple.y + 30) && (y >= apple.y)) ||
            ((y+30 <= apple.y + 30) && (y+30 >= apple.y)))
    {
        if ((x + 30 >= apple.x && x + 30 <= apple.x + 30) ||
                (x >= apple.x && x <= apple.x + 30))
        {
            return true;
        }

    }

    return false;
}
bool Snake::check_head_collision()
{
    for (int i = 1; i != length ;i++)
    {
        if (position[i].y == y && position[i].x == x)
            return true;
    }
    if (y > 601 || y < -1 || x > 801 || x < -1)
        return true;
    return false;

}
bool Snake::check_collision_body(Apple apple)
{
    for (int i = length - 1; i>=0 ; i--)
    {
        if (((position[i].y <= apple.y + 30) && (position[i].y >= apple.y)) ||
                ((position[i].y+30 <= apple.y + 30) && (position[i].y+30 >= apple.y)))
        {
            if ((position[i].x + 30 >= apple.x && position[i].x + 30 <= apple.x + 30) ||
                    (position[i].x >= apple.x && position[i].x <= apple.x + 30))
            {
                return true;
            }

        }
    }

    return false;


}
