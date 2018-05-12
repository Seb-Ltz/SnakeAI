#include <iostream>
#include <cmath>
#include "AISnake.h"

AISnake::AISnake(unsigned short sizeX, unsigned short sizeY)
        : Snake(sizeX, sizeY)
        , neuralNetwork(6, 3, 0, 4)
{
    neuralNetwork.mutate(100, 100);
}
AISnake::AISnake(unsigned short sizeX, unsigned short sizeY, NeuralNetwork neuralNetwork)
        : Snake(sizeX, sizeY)
        , neuralNetwork(neuralNetwork)
{
}

int AISnake::getDirection() {
    //Calculate the distance between snake head and food for calculating the score
    foodDistance = pow(snakeHead.x - foodPos.x, 2) + pow(snakeHead.y - foodPos.y, 2);

    //Calculate the inputs
    double isFoodLeft = calcFoodLeft();
    double isFoodAhead = calcFoodAhead();
    double isFoodRight = calcFoodRight();

    double isClearLeft = calcClearLeft();
    double isClearAhead = calcClearAhead();
    double isClearRight = calcClearRight();

    std::vector<double> inputValues = {isFoodLeft, isFoodAhead, isFoodRight, isClearLeft, isClearAhead, isClearRight};

    neuralNetwork.setInput(inputValues);

    const std::vector<double> output = neuralNetwork.getOutput();
    if(output[0] > output[1] && output[0]){};


    //get the index (distance()) in the output with the greatest output value;
    int outputIndex = std::distance(output.begin(), std::max_element(output.begin(), output.end()));
    if(outputIndex == 0) {
        return 0;
    }
    if(outputIndex == 1) {
        return -1;
    }
    return 1;

}

double AISnake::finishGame() {
    while(!isDead() && aiScore > -(sizeX * sizeY)) {
        step();
    }

    return aiScore;
}

void AISnake::snakeMoveEvent() {
    //CALCULATE NEW SCORE

    //Is the snake going nearer to the food ?
    double newFoodDist = pow(snakeHead.x - foodPos.x, 2) + pow(snakeHead.y - foodPos.y, 2);
    if(newFoodDist < foodDistance) {
        aiScore += MOVE_TOWARDS_SCORE;
    } else {
        aiScore += MOVE_AWAY_SCORE;
    }

}

void AISnake::foodEvent() {
    //To counter the effects of moving away that turn
    aiScore += FOOD_SCORE - MOVE_AWAY_SCORE;
}

void AISnake::deathEvent() {
}

double AISnake::calcFoodAhead() {
    if(direction.x == 1) {
        return snakeHead.y == foodPos.y && snakeHead.x <= foodPos.x ? 1 : 0;
    } else if (direction.x == -1) {
        return snakeHead.y == foodPos.y && snakeHead.x >= foodPos.x ? 1 : 0;
    } else if(direction.y == 1) {
        return snakeHead.x == foodPos.x && snakeHead.x <= foodPos.x ? 1 : 0;
    } else {
        return snakeHead.x == foodPos.x && snakeHead.x >= foodPos.x ? 1 : 0;
    }
}

double AISnake::calcFoodLeft() {
    if(direction.x == 1) {
        return snakeHead.y > foodPos.y;
    } else if (direction.x == -1) {
        return snakeHead.y < foodPos.y;
    } else if(direction.y == 1) {
        return snakeHead.x < foodPos.x;
    } else {
        return snakeHead.x > foodPos.x;
    }
}

double AISnake::calcFoodRight() {
    if(direction.x == 1) {
        return snakeHead.y < foodPos.y;
    } else if (direction.x == -1) {
        return snakeHead.y > foodPos.y;
    } else if(direction.y == 1) {
        return snakeHead.x > foodPos.x;
    } else {
        return snakeHead.x < foodPos.x;
    }
}

double AISnake::calcClearAhead() {
    sf::Vector2i newSnakeHead = snakeHead + direction;

    return isPositionClear(newSnakeHead) ? 1 : 0;
}

double AISnake::calcClearLeft() {
    sf::Vector2i leftDir = sf::Vector2i(direction.y, -direction.x);
    sf::Vector2i newSnakeHead = snakeHead + leftDir;

    return isPositionClear(newSnakeHead) ? 1 : 0;
}

double AISnake::calcClearRight() {
    sf::Vector2i leftDir = sf::Vector2i(-direction.y, +direction.x);
    sf::Vector2i newSnakeHead = snakeHead + leftDir;

    return isPositionClear(newSnakeHead) ? 1 : 0;

}

bool AISnake::isPositionClear(sf::Vector2i position) {
    //It's outside of the game
    if(position.x > sizeX - 1 || position.x < 0 || position.y > sizeY - 1 || position.y < 0) {
        return false;
    }

    //Or snakeHead is on the snake
    if(std::find(snake.begin(), snake.end(), position) != snake.end()) {
        return false;
    }

    return true;
}

double AISnake::getAiScore() const {
    return aiScore;
}

const NeuralNetwork &AISnake::getNeuralNetwork() const {
    return neuralNetwork;
}
