#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Math.h"

#define DPI (3.141592 * 2)

Snake::Snake(unsigned short sizeX, unsigned short sizeY)
    : sizeX(sizeX), sizeY(sizeY)
{
    unsigned int middleX = round(sizeX / 2.0);
    unsigned int middleY = round(sizeY / 2.0);

    snake.push_back(sf::Vector2i(middleX, middleY + 2));
    snake.push_back(sf::Vector2i(middleX, middleY + 1));
    snake.push_back(sf::Vector2i(middleX, middleY - 0));
    snake.push_back(sf::Vector2i(middleX, middleY - 1));

    snakeHead = sf::Vector2i(middleX, middleY - 1);

    direction = sf::Vector2i(0, -1);

    generateFood();
}

void Snake::step() {
    //Calculate the new position of the snake

    int newDir = getDirection();

    if(newDir == -1) {
        direction = sf::Vector2i(direction.y, -direction.x);
    } else if(newDir == 1) {
        direction = sf::Vector2i(-direction.y, +direction.x);
    }

    sf::Vector2i newSnakeHead = sf::Vector2i(snakeHead + direction);

    //If snakehead is outside of game
    if(newSnakeHead.x > sizeX - 1 || newSnakeHead.x < 0 || newSnakeHead.y > sizeY - 1 || newSnakeHead.y < 0) {
        snakeDead = true;
        deathEvent();
        return;
    }
    //Or snakeHead is on the snake
    if(std::find(snake.begin(), snake.end(), newSnakeHead) != snake.end()) {
        snakeDead = true;
        deathEvent();
        return;
    }

    snake.push_back(newSnakeHead);
    snakeHead = newSnakeHead;

    snakeMoveEvent();

    if(shouldEraseTail) {
        snake.erase(snake.begin()); //erase the first inputValue
    } else {
        shouldEraseTail = true;
    }


    if(snakeHead == foodPos) {
        generateFood();
        gameScore++;
        foodEvent();
        shouldEraseTail = false;
    }

    stepsCount++;

    colorId++;
}

void Snake::generateFood() {
    unsigned int posX;
    unsigned int posY;

    //Prevent from spawning food on the snake directly
    while(true) {
        posX = static_cast<unsigned int>(rand() % sizeX); //Between [0 ; sizeX[
        posY = static_cast<unsigned int>(rand() % sizeY); //Between [0 ; sizeY[

        if(std::find(snake.begin(), snake.end(), sf::Vector2i(posX, posY)) != snake.end()) {
            /* food spawned on snake */
        } else {
            /* food spawned not on the snake */
            break;
        }
    }

    foodPos = sf::Vector2i(posX, posY);
}

void Snake::render(sf::RenderWindow &window) {
    //Create a snake game to render

    //White background
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(sizeX, sizeY));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(0, 0);
    window.draw(rect);

    //Snake
    rect.setSize(sf::Vector2f(1, 1));
    if(isDead()) {
        rect.setFillColor(sf::Color(200, 100, 100));
    } else {
        rect.setFillColor(sf::Color(100, 100, 100));
    }
    for(unsigned int i = 0; i < snake.size(); i++) {
        rect.setPosition(snake[i].x, snake[i].y);
        //Purple gradient
        //rect.setFillColor(sf::Color(255 - (((float)i / snake.size()) * 200), 255 - (((float)i / snake.size()) * 127 + 127), ((float)i / snake.size()) * 127 + 127));
        //Rainbow
        rect.setFillColor(sf::Color(
                                    sin(((i + colorId) / 6.0) + (DPI / 3) * 0) * 127 + 127,
                                    sin(((i + colorId) / 6.0) + (DPI / 3) * 1) * 127 + 127,
                                    sin(((i + colorId) / 6.0) + (DPI / 3) * 2) * 127 + 127));
        window.draw(rect);
    }

    //Food
    sf::Vector2i foodPos = getFoodPos();
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(foodPos.x * rect.getSize().x, foodPos.y * rect.getSize().y);
    window.draw(rect);

}

int Snake::getDirection() {
    //-1: left, 0: forward, 1: right
    return 0;
}

//Events
void Snake::foodEvent() {

}
void Snake::deathEvent() {

}
void Snake::snakeMoveEvent() {

}

//Getters
const sf::Vector2i &Snake::getFoodPos() const {
    return foodPos;
}
bool Snake::isDead() const {
    return snakeDead;
}
