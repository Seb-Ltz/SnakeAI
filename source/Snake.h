
#pragma once

#include <vector>
#include <queue>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Snake {
public:
    Snake(unsigned short sizeX, unsigned short sizeY);
    void step();

    const sf::Vector2i &getFoodPos() const;
    void render(sf::RenderWindow &window);
    bool isDead() const;

protected:
    virtual int getDirection();

    virtual void foodEvent();
    virtual void deathEvent();
    virtual void snakeMoveEvent();


    sf::Vector2i snakeHead;
    sf::Vector2i foodPos;
    sf::Vector2i direction;
    unsigned short sizeX, sizeY;

    std::vector<sf::Vector2i> snake;

private:
    void generateFood();

    unsigned int gameScore = 0;
    unsigned int stepsCount = 0;

    bool shouldEraseTail = true;
    bool snakeDead = false;

    unsigned int colorId = 0;
};



