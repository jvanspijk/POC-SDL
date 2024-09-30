#pragma once

class Player {
public:
    Player(float x, float y, float speed);

    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void updatePosition(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float deltaTime);

    float getX() const;
    float getY() const;

private:
    float x;
    float y;
    float speed;
};