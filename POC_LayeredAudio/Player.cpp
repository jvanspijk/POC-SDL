#include "Player.h"

Player::Player(float x, float y, float speed) : x(x), y(y), speed(speed) {}

void Player::moveUp(float deltaTime) {
    y -= speed * deltaTime;
}

void Player::moveDown(float deltaTime) {
    y += speed * deltaTime;
}

void Player::moveLeft(float deltaTime) {
    x -= speed * deltaTime;
}

void Player::moveRight(float deltaTime) {
    x += speed * deltaTime;
}

void Player::updatePosition(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float deltaTime) {
    if (moveUp) this->moveUp(deltaTime);     
    if (moveDown) this->moveDown(deltaTime); 
    if (moveLeft) this->moveLeft(deltaTime); 
    if (moveRight) this->moveRight(deltaTime);
}


float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}