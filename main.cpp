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
class Apple :public sf::Transformable, public Snake{
public:
    Pos position;
    float x;
    float y;
    sf::Texture apple_texture;
    sf::Sprite apple;

    bool load_files()
    {
        if (!apple_texture.loadFromFile("img/apple.png"))
            return false;

        apple.setTexture(apple_texture);

        return true;
    }

    void check_snake_body(Pos pos, int len)
    {
        //if
    }

    void rand_position()
    {
        do
        {
        position.x = (rand() % 750) + 10;
        position.y = (rand() % 550) + 10;
        x = position.x;
        y = position.y;
        apple.setPosition(x,y);
        cout <<"trying"<<endl;
        } while ();
        cout << "app position = " << x << ", " << y<< endl;
    }

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
        return true;
    }

    void move_snake(int key)
    {
        position[0].x = x;
        position[0].y = y;
        //  W
        //A S D

        //  1
        //2 3 4
        switch (key)
        {
        case 1:
            y-=30;
            break;
        case 2:
            x-=30;
            break;
        case 3:
            y+=30;
            break;
        case 4:
            x+=30;
            break;
        }
        head.setPosition(x,y);
        for (int i = length - 1; i != 0 ; i--)
        {
            position[i] = position[i-1];
        }
    }

    void draw(sf::RenderWindow &window)
    {

        window.draw(head);
        for (int i = length - 1; i != 0 ; i--)
        {
            body.setPosition(position[i].x, position[i].y);
            window.draw(body);
        }
    }

    bool check_collision(Apple &apple)
    {
        if (((y <= apple.y + 30) && (y >= apple.y)) ||
            ((y+30 <= apple.y + 30) && (y+30 >= apple.y)))
        {
            if ((x + 30 >= apple.x && x + 30 <= apple.x + 30) ||
                (x >= apple.x && x <= apple.x + 30))
                    {
                        return true;
                        //apple.rand_position();
                        //length+=1;
                    }

        }

        return false;


        //    if ((y < pipes.y_up+pipes.pipe_len && y > pipes.y_up) ||
   //         (y < pipes.y_down+pipes.pipe_len && y > pipes.y_down) ||
    //        (y+length < pipes.y_up+pipes.pipe_len && y + length > pipes.y_up) ||
   //         (y+length < pipes.y_down+pipes.pipe_len && y + length > pipes.y_down))
 //   {
  //      if (x + width > pipes.x && x + width < pipes.x + pipes.pipe_width)
  //          return true;
    }

};
int main()
{
    srand(time(NULL));
    sf::Time cooldown;
    cooldown = sf::seconds( 0.1f );
    sf::Clock frameclock;
    sf::Time elapsedtime;
    sf::RenderWindow window(sf::VideoMode(800,600), "Flappy Me!"); // tworzenie glownego okna
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    int key;
    Apple apple;
    apple.load_files();
    apple.rand_position();
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                key = 2;
                cout << snake.x << endl << snake.y << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                key = 3;
                cout << snake.x << endl << snake.y << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                key = 4;
                cout << snake.x << endl << snake.y << endl;
            }

        }
        elapsedtime += frameclock.restart();
        if( elapsedtime >= cooldown )
        {
            elapsedtime = sf::Time::Zero;
            snake.move_snake(key);
        }
        if(snake.check_collision(apple))
        {
            cout << "collision" << endl;
        }
        window.clear(); // czyszczenie okna
        window.draw(apple.apple);
        snake.draw(window);
        //window.draw(background_sprite);
        //window.draw(snake.head);
        window.display();
    }

    return 0;
}
