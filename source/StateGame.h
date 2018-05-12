
#pragma once


#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "AISnake.h"

class StateGame {

public:
    StateGame(sf::Vector2u viewportSize);

    void update(float dt);
    void render(sf::RenderWindow &window);

    virtual ~StateGame();

private:
    sf::View gameView;
    AISnake* snakeGame;
    unsigned short gameSizeX = 20;
    unsigned short gameSizeY = 20;

    NeuralNetwork bestNeuralNetwork;
    NeuralNetwork getBestNeuralNetwork(unsigned int tries);

};



