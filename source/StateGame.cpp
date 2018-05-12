#include <iostream>
#include "StateGame.h"
#include "AISnake.h"

StateGame::StateGame(sf::Vector2u viewportSize) : bestNeuralNetwork(0, 0, 0, 0)
{
    float ratioY = viewportSize.y / gameSizeY;
    float ratioX = viewportSize.x / gameSizeX;


    gameView = sf::View(sf::Vector2f(gameSizeX / 2.0f, gameSizeY / 2.0f), sf::Vector2f(ratioX, ratioY));

    bestNeuralNetwork = getBestNeuralNetwork(1000);
    snakeGame = new AISnake(gameSizeX, gameSizeY, bestNeuralNetwork);

}

void StateGame::update(float dt) {

    if(!snakeGame->isDead() && snakeGame->getAiScore() > -5) {
        snakeGame->step();
    } else {
        std::cout << "SCORE = " << snakeGame->getAiScore() << std::endl;
        snakeGame = new AISnake(gameSizeX, gameSizeY, bestNeuralNetwork);
    }
}

void StateGame::render(sf::RenderWindow &window) {
    window.setView(gameView);

    snakeGame->render(window);

}

NeuralNetwork StateGame::getBestNeuralNetwork(unsigned int tries) {
    //Get the best neural network with the greatest score
    NeuralNetwork neuralNetwork(0, 0, 0, 0);
    double bestScore = 0;

    for(int i = 0; i < tries; i++) {
        snakeGame = new AISnake(gameSizeX, gameSizeY);
        double score = snakeGame->finishGame();

        if(score> bestScore) {
            bestScore = score;
            neuralNetwork = snakeGame->getNeuralNetwork();
            std::cout << "New best = " << bestScore << std::endl;
        }

        delete snakeGame;
    }

    return neuralNetwork;

}

StateGame::~StateGame() {
    delete snakeGame;
}
