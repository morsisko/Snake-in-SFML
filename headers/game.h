#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
class Results;
class Game :public sf::Transformable
{
    Results results;
    sf::RenderWindow window;
    sf::Font font;
    enum GameState {MENU, GAME, GAME_OVER, SCORE, OPTIONS, SPECIAL_MENU, END};
    GameState state;
    //declaring background
    sf::Texture background;
    sf::Texture list_texture;
    sf::Texture secret_background;
    sf::Texture mini_texture;
    sf::Texture mini_grass_texture;
    sf::Texture mini_sand_texture;
    sf::Texture map1_texture;
    sf::Texture map2_texture;
    sf::Texture map3_texture;
    sf::Sprite background_sprite;
    sf::Sprite list_sprite;
    sf::Sprite secret_background_sprite;
    sf::Sprite mini_sprite;
    sf::Sprite map1;
    sf::Sprite mini_grass;
    sf::Sprite map2;
    sf::Sprite mini_sand;
    sf::Sprite map3;
    //others
    bool sounds = true;
    std::string actuall_code = ""; // string to konami code
    bool konami_menu = false;
    bool konami = false;
    int mode = 0;
public:
    Game();

    bool add_code(char code);

    void run();

    void start_game();

    void menu();

    void score();

    void options();

    void special_menu();
};
