
#pragma once


#include "Snake.h"
#include "NeuralNetwork.h"

class AISnake : public Snake {
public:
    AISnake(unsigned short sizeX, unsigned short sizeY);
    AISnake(unsigned short sizeX, unsigned short sizeY, NeuralNetwork neuralNetwork);

    double finishGame();

    double getAiScore() const;
    const NeuralNetwork &getNeuralNetwork() const;

protected:
    int getDirection() override;

    void foodEvent() override;
    void deathEvent() override;
    void snakeMoveEvent() override;

private:
    double aiScore = 0;
    const double FOOD_SCORE = 20;
    const double MOVE_TOWARDS_SCORE = 1;
    const double MOVE_AWAY_SCORE = -1.5;

    double foodDistance;

    //INPUTS
    double calcFoodLeft();
    double calcFoodAhead();
    double calcFoodRight();
    double calcClearLeft();
    double calcClearAhead();
    double calcClearRight();

    bool isPositionClear(sf::Vector2i position);

    NeuralNetwork neuralNetwork;
};



