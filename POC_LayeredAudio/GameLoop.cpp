#include "GameLoop.h"

GameLoop::GameLoop(AudioManager* audioManager, Renderer* renderer, InputHandler* inputHandler, Player* player)
    : audioManager(audioManager), inputHandler(inputHandler), renderer(renderer), player(player) {}

void GameLoop::run() {
    bool quit = false;
    bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

    const float deltaTime = 0.016f; // Hardcoded frame timing will have to do for now

    while (!quit) {
        inputHandler->handleInput(quit, moveUp, moveDown, moveLeft, moveRight);
        player->updatePosition(moveUp, moveDown, moveLeft, moveRight, deltaTime);

        renderer->clearScreen();
        renderer->renderPlayer(player->getX(), player->getY());
        renderer->presentScreen();
    }
}