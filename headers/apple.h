#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Snake;
class Apple :public sf::Transformable{
public:
    float x;
    float y;
    sf::Texture apple_texture;
    sf::Sprite apple;

    bool load_files();

    void rand_position();

};
