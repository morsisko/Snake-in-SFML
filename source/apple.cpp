#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include "../headers/apple.h"
#include "../headers/snake.h"
using namespace std;

bool Apple::load_files(int mode)
{
    if (!apple_texture.loadFromFile("img/apple.png"))
        return false;

    if (!star_texture.loadFromFile("img/star.png"))
        return false;

    if (!banana_texture.loadFromFile("img/banana.png"))
        return false;

    if (!mode || mode == 2) apple.setTexture(apple_texture);
    else if (mode == 1) apple.setTexture(star_texture);
    else if (mode == 3) apple.setTexture(banana_texture);

    return true;
}

void Apple::rand_position()
{

    x = (rand() % 750) + 10;
    y = (rand() % 550) + 10;
    apple.setPosition(x,y);
    //cout <<"trying"<<endl;
    //cout << "app position = " << x << ", " << y<< endl;
}

string Apple::return_points()
{
    stringstream points_ss;
    points_ss << score_to_get;
    string points_to_view = points_ss.str();
    return points_to_view;
}





