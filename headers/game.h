#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
class Results;
class Game :public sf::Transformable
{
    std::string actuall_code = "";
    bool konami = false;
    Results results;
    sf::RenderWindow window;
    sf::Font font;
    enum GameState {MENU, GAME, GAME_OVER, SCORE, OPTIONS, END};
    GameState state;
    //declaring background
    sf::Texture background;
    sf::Texture list_texture;
    sf::Texture secret_background;
    sf::Sprite background_sprite;
    sf::Sprite list_sprite;
    sf::Sprite secret_background_sprite;
public:
    Game();

    void add_code(char code);

    void run();

    void start_game();

    void menu();

    void score();

    void options();
};
