#include "GameLoop.h"

GameLoop::GameLoop(AudioManager* audioManager, Renderer* renderer, InputHandler* inputHandler, Player* player)
    : audioManager(audioManager), inputHandler(inputHandler), renderer(renderer), player(player) {}

void GameLoop::run() {
    bool quit = false;
    bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false, adaptiveMode = false;
    float bpm = 108.0f;
    float timeScale = 1.0f;

    float lastBaseVolume = 0.0f;     
    float lastIntensityVolume = 0.0f;

    float lastPlaybackSpeed = 1.0f;

    Uint32 lastTime = SDL_GetTicks();
    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = ((currentTime - lastTime) / 1000.0f) * timeScale;
        lastTime = currentTime;

        renderer->clearScreen(adaptiveMode, deltaTime, bpm * timeScale);
        renderer->renderPlayer(player->getX(), player->getY());
        renderer->presentScreen();

        const float desiredBaseVolume = adaptiveMode ? 1.0f : 0.75f;
        const float desiredIntensityVolume = adaptiveMode ? 1.0f : 0.0f;

        // Change volume only if it has changed
        if (desiredBaseVolume != lastBaseVolume || desiredIntensityVolume != lastIntensityVolume) {
            audioManager->setVolume(desiredBaseVolume, desiredIntensityVolume);
            lastBaseVolume = desiredBaseVolume; 
            lastIntensityVolume = desiredIntensityVolume;
        }

        float desiredPlaybackSpeed = timeScale;

        // Set playback speed only if it has changed
        if (desiredPlaybackSpeed != lastPlaybackSpeed) {
            audioManager->setSpeed(desiredPlaybackSpeed);
            lastPlaybackSpeed = desiredPlaybackSpeed; 
        }

        inputHandler->handleInput(quit, moveUp, moveDown, moveLeft, moveRight, adaptiveMode, timeScale);
        player->updatePosition(moveUp, moveDown, moveLeft, moveRight, deltaTime);
    }
}