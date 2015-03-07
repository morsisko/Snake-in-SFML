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

class Snake :public sf::Transformable
{
public:
    sf::Texture head_texture;
    sf::Texture body_texture;
    sf::Sprite head;
    sf::Sprite body;
    Pos position[600];
    float x = 300;
    float y = 300;
    int length = 1;

public:

    bool load_files()
    {
        if (!head_texture.loadFromFile("img/head.png"))
            return false;

        head.setTexture(head_texture);

        if (!body_texture.loadFromFile("img/part.png"))
            return false;

        body.setTexture(body_texture);

        position[0].x = x;
        position[0].y = y;
        head.setPosition(x,y);
        return true;
    }

    void move_snake(int key)
    {
        //  W
        //A S D

        //  1
        //2 3 4
        switch (key)
        {
            case 1:
                y--;
                break;
            case 2:
                x--;
                break;
            case 3:
                y++;
                break;
            case 4:
                x++;
                break;
        }
        position[0].x = x;
        position[0].y = y;
        head.setPosition(x,y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(head);
    }

};
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Me!"); // tworzenie glownego okna
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    int key;
    Snake snake;
    if (snake.load_files() == false)
        return -1;
    sf::Texture background;
    if (!background.loadFromFile("img/background.png"))
        return -1;
    sf::Sprite background_sprite; // sprite tla
    background_sprite.setTexture(background);
    background_sprite.setPosition(0,0); // ustawianie spritow
    while (window.isOpen()) // glowna petla
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                key = 1;
                cout << snake.x << endl << snake.y << endl;
            }

        }
        //snake.move_snake(key);
        window.clear(); // czyszczenie okna
        //snake.draw(window);
        window.draw(background_sprite);
        //window.draw(snake.head);
    }

    return 0;
}
