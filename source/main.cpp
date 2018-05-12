#include <SFML/Graphics.hpp>
#include "StateGame.h"

int main()
{
    srand(time(NULL));

    StateGame game(sf::Vector2u(1280, 720));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Snake Genetic Algorithm");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.update(0.0f);

        window.clear();
        game.render(window);
        window.display();
    }

    return 0;
}