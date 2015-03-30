#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace std;
struct Pos
{
    float x;
    float y;
};
class Apple;
class Snake :public sf::Transformable
{
public:
    sf::Texture head_texture;
    sf::Texture body_texture;
    sf::Sprite head;
    sf::Sprite body;
    sf::SoundBuffer get_point_buffer;
    sf::Sound get_point;
    Pos position[600];
    float x = 300;
    float y = 300;
    float speed = 30;
    int length = 1;
    int score = 0;

public:

    bool load_files();

    void move_snake(int key);

    void draw(sf::RenderWindow &window);

    bool check_collision(Apple &apple);

    bool check_head_collision();

    bool check_collision_body(Apple &apple);

    string return_points(int points);

};
