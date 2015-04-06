#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstring>
#include "../headers/snake.h"
#include "../headers/apple.h"
#include "../headers/results.h"
#include "../headers/game.h"

using namespace sf;
using namespace std;

Game::Game()
{
    state = END;
    //loading files
    if (!font.loadFromFile("fonts/angrybirds-regular.ttf"))
        return;
    if (!background.loadFromFile("img/background.png"))
        return;
    if (!list_texture.loadFromFile("img/list.png"))
        return;
    if (!secret_background.loadFromFile("img/rainbow.png"))
        return;
    if (!results.import_file())
        return;
    //creating and setting window
    window.create(sf::VideoMode(1000, 600), "Snake");
    window.setFramerateLimit(60); // ustalenie limitu na 60 fps
    window.setKeyRepeatEnabled(false);
    //setting background
    background_sprite.setTexture(background);
    background_sprite.setPosition(0,0);
    list_sprite.setTexture(list_texture);
    list_sprite.setPosition(810,0);
    secret_background_sprite.setTexture(secret_background);
    secret_background_sprite.setPosition(0,0);
    //without errors
    state = MENU;
}

void Game::add_code(char code)
{
    if (code == 0) return;
    if (actuall_code.length() < 10) actuall_code += code;
    else
    {
        for (int i = 0; i != 9; i++)
        {
            actuall_code[i] = actuall_code[i+1];
        }
        actuall_code[9] = code;
    }
    if (actuall_code == "UUDDLRLRBA") konami = true;
    cout << actuall_code << std::endl;
}

void Game::run()
{
    while (state != END)
    {
        switch (state)
        {
        case MENU:
            menu();
            break;
        case GAME:
            start_game();
            break;
        case GAME_OVER:
            state = GAME;
            start_game();
            break;
        case SCORE:
            score();
            break;
        case OPTIONS:
            options();
            break;
        case END:
            break;
        }
    }

}

void Game::start_game()
{
    actuall_code = "";
    bool die = false;
    //declaring time variables
    sf::Time cooldown;
    sf::Time points_cooldown;
    sf::Time elapsedtime;
    sf::Time elapsed_points_time;
    //setting time variables
    cooldown = sf::seconds( 0.1f );
    points_cooldown = sf::seconds ( 0.05f );
    //declaring clock variables
    sf::Clock frameclock;
    sf::Clock points_clock;
    //declaring text variables
    sf::Text points;
    sf::Text score_to_get_text;
    sf::Text score_text;
    sf::Text error;
    sf::Text best_length;
    sf::Text best_score;
    //creating apple and snake
    Apple apple;
    Snake snake;
    //loading images
    if (snake.load_files() == false)
        return;
    if (apple.load_files() == false)
        return;
    //setting apple position
    apple.rand_position();
    //setting text variables
    points.setFont(font);
    points.setPosition(820,40);
    points.setCharacterSize(35);
    score_to_get_text.setFont(font);
    score_to_get_text.setPosition(820,140);
    score_to_get_text.setCharacterSize(35);
    score_text.setFont(font);
    score_text.setPosition(820,240);
    score_text.setCharacterSize(35);
    best_length.setFont(font);
    best_length.setPosition(820,340);
    best_length.setCharacterSize(35);
    best_score.setFont(font);
    best_score.setPosition(820,440);
    best_score.setCharacterSize(35);
    error.setFont(font);
    error.setPosition(50, 200);
    error.setCharacterSize(80);
    error.setString("You lost! Press ENTER to play again!");


    //dif
    int key = rand() % 4 + 1; // snake direction

    while (state == GAME) // glowna petla
    {
        die = !snake.speed;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                state = MENU;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                key = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                key = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                key = 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                key = 4;
            }
            if (die && Keyboard::isKeyPressed(Keyboard::Return))
            {
                state = GAME_OVER;
            }

        }
        elapsedtime += frameclock.restart(); // timer to moving snake
        elapsed_points_time += points_clock.restart(); // elapsed time since last eaten apple
        if( elapsedtime >= cooldown )
        {
            elapsedtime = sf::Time::Zero;
            if(snake.check_head_collision())
            {
                snake.speed = 0;
                if(results.check(snake.length, 1)) results.save();
                if(results.check(snake.score, 2)) results.save();
            }
            else
            {
                snake.move_snake(key);
            }

            points.setString("Length: " + snake.return_points(snake.length));
            score_to_get_text.setString("To get: " + apple.return_points());
            score_text.setString("Score: " + snake.return_points(snake.score));
            best_length.setString("Best: " + results.return_points(1));
            best_score.setString("Best: " + results.return_points(2));

        }
        if (elapsed_points_time >= points_cooldown && apple.score_to_get > 0)
        {
            elapsed_points_time = sf::Time::Zero;
            apple.score_to_get -= 1;
        }
        if(snake.check_collision(apple))
        {
            snake.length+=1;
            snake.get_point.play();
            snake.score += apple.score_to_get;
            apple.score_to_get = 100;
            do
            {
                apple.rand_position();
            }
            while (snake.check_collision_body(apple));

        }
        window.clear(); // czyszczenie okna
        if (konami) window.draw(secret_background_sprite);
        else window.draw(background_sprite);
        snake.draw(window);
        window.draw(list_sprite);
        window.draw(points);
        window.draw(score_text);
        window.draw(score_to_get_text);
        window.draw(best_length);
        window.draw(best_score);
        window.draw(apple.apple);
        if (die) window.draw(error);
        window.display();
    }

}

void Game::menu()
{
    Text title("Snake by morsisko", font, 75);
    title.setStyle(Text::Bold);
    title.setColor(Color::Red);

    title.setPosition(250, 20);

    const int buttons = 4; // number of buttons

    Text buttons_text[buttons];

    string str[] = {"Play", "Score", "Options", "Exit"};
    for (int i = 0; i < buttons; i++)
    {
        buttons_text[i].setFont(font);
        buttons_text[i].setCharacterSize(65);
        buttons_text[i].setString(str[i]);
        buttons_text[i].setPosition(400, 150+(i*120));

    }

    while (state == MENU)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
            {
                state = END;
            }

            else if (buttons_text[0].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = GAME;
            }

            else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = SCORE;
            }

            else if (buttons_text[2].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = OPTIONS;
            }
            else if (buttons_text[3].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = END;
            }

            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Up) add_code('U');
            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Down) add_code ('D');
            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Left) add_code  ('L');
            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Right) add_code ('R');
            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::B) add_code ('B');
            else if (event.type == sf::Event::KeyPressed && event.key.code == Keyboard::A) add_code ('A');
        }

        window.clear();

        for (int i = 0; i<buttons; i++) // buttons = len of tab buttons_tab
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
            {
                buttons_text[i].setColor(Color::Yellow);
            }
            else
            {
                buttons_text[i].setColor(Color::White);
            }

            window.draw(buttons_text[i]);
        }

        window.draw(title);
        window.display();

    }
}

void Game::score()
{
    Text title("Score", font, 75);
    title.setStyle(Text::Bold);
    title.setColor(Color::Red);

    title.setPosition(250, 20);

    const int buttons = 3; // number of buttons

    Text buttons_text[buttons];
    string best_lenght = results.return_points(1);
    string best_score = results.return_points(2);

    string str[] = {"Best lenght " + best_lenght, "Best score " + best_score, "Return to menu"};
    for (int i = 0; i < buttons; i++)
    {
        buttons_text[i].setFont(font);
        buttons_text[i].setCharacterSize(65);
        buttons_text[i].setString(str[i]);
        buttons_text[i].setPosition(400, 150+(i*120));

    }

    while (state == SCORE)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
            {
                state = END;
            }

            else if (buttons_text[2].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = MENU;
            }
        }

        window.clear();

        for (int i = 0; i<buttons; i++) // buttons = len of tab buttons_tab
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
            {
                buttons_text[i].setColor(Color::Yellow);
            }
            else
            {
                buttons_text[i].setColor(Color::White);
            }

            window.draw(buttons_text[i]);
        }

        window.draw(title);
        window.display();

    }
}

void Game::options()
{
    Text title("Options", font, 75);
    title.setStyle(Text::Bold);
    title.setColor(Color::Red);

    title.setPosition(250, 20);

    const int buttons = 2; // number of buttons

    Text buttons_text[buttons];

    string str[] = {"Sounds: ON", "Return to menu"};
    for (int i = 0; i < buttons; i++)
    {
        buttons_text[i].setFont(font);
        buttons_text[i].setCharacterSize(65);
        buttons_text[i].setString(str[i]);
        buttons_text[i].setPosition(400, 150+(i*120));

    }

    while (state == OPTIONS)
    {
        Vector2f mouse(Mouse::getPosition(window));
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
            {
                state = END;
            }

            else if (buttons_text[0].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                ;//TODO
            }

            else if (buttons_text[1].getGlobalBounds().contains(mouse) &&
                     Mouse::isButtonPressed(Mouse::Left))
            {
                state = MENU;
            }
        }

        window.clear();

        for (int i = 0; i<buttons; i++) // buttons = len of tab buttons_tab
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
            {
                buttons_text[i].setColor(Color::Yellow);
            }
            else
            {
                buttons_text[i].setColor(Color::White);
            }

            window.draw(buttons_text[i]);
        }

        window.draw(title);
        window.display();

    }
}



