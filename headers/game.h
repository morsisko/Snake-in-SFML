#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

class Game :public sf::Transformable
{
    Results results;
    sf::RenderWindow window;
    sf::Font font;
    enum GameState {GAME, GAME_OVER, SCORE, END, MENU};
    GameState state;
    //declaring background
    sf::Texture background;
    sf::Sprite background_sprite;
public:
    Game();

    void run();

    void start_game();

    void menu();

    void score();
};
