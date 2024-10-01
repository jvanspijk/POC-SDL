#include "GameLoop.h"

GameLoop::GameLoop(AudioManager* audioManager, Renderer* renderer, InputHandler* inputHandler, Player* player)
    : audioManager(audioManager), inputHandler(inputHandler), renderer(renderer), player(player) {}

void GameLoop::run() {
    bool quit = false;
    bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false, adaptiveMode = false;
    float bpm = 108.0f;
    float timeScale = 1.0f;
    
    Uint32 lastTime = SDL_GetTicks();
    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = ((currentTime - lastTime) / 1000.0f);
        lastTime = currentTime;

        renderer->clearScreen(adaptiveMode, deltaTime, bpm * timeScale);
        renderer->renderPlayer(player->getX(), player->getY());
        renderer->presentScreen();

        if (adaptiveMode) {
            audioManager->fadeIn("layer2", 1);
        }
        else {
            audioManager->fadeOut("layer2", 1);
        }        

        inputHandler->handleInput(quit, moveUp, moveDown, moveLeft, moveRight, adaptiveMode, timeScale);
        player->updatePosition(moveUp, moveDown, moveLeft, moveRight, deltaTime);
    }
}