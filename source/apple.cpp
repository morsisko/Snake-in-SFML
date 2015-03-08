#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../headers/apple.h"
#include "../headers/snake.h"
using namespace std;

bool Apple::load_files()
{
    if (!apple_texture.loadFromFile("img/apple.png"))
        return false;

    apple.setTexture(apple_texture);

    return true;
}

void Apple::rand_position()
{
    x = (rand() % 750) + 10;
    y = (rand() % 550) + 10;
    apple.setPosition(x,y);
    cout <<"trying"<<endl;
    cout << "app position = " << x << ", " << y<< endl;
}





