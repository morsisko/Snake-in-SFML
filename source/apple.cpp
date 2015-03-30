#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
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

string Apple::return_points()
{
    stringstream points_ss;
    points_ss << score_to_get;
    string points_to_view = points_ss.str();
    return points_to_view;
}





