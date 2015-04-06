#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../headers/snake.h"
#include "../headers/apple.h"
#include "../headers/results.h"
#include "../headers/game.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Game game;
    game.run();
    return 0;
}
