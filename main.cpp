#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Me!"); // tworzenie glownego okna
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    cout << "Hello world!" << endl;


    while (window.isOpen()) // glowna petla
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
           // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            //{
            //}

        }
     window.clear(); // czyszczenie okna
    }

 return 0;
}
