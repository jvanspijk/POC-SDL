#define SDL_MAIN_HANDLED
#include "AudioManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "GameLoop.h"
#include <iostream>

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return -1;
    }

    const int width = 1366;
    const int height = 768;

    window = SDL_CreateWindow("Press the spacebar for an epilepsy attack (PGUP and PGDOWN control speed)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        return -1;
    }

    Renderer renderer(window);
    const int amountOfAudioChannels = 8;
    const int baseFrequency = 44100;

    AudioManager audioManager;    

    audioManager.loadMusic("Synthwave_layer1.ogg", "Synthwave_layer2.ogg");
    audioManager.playMusic();
    audioManager.setVolume(1.0f, 0.0f);

    InputHandler inputHandler;

    const int playerStartX = 400;
    const int playerStartY = 300;
    const float playerSpeed = 250.0f;
    Player player(playerStartX, playerStartY, playerSpeed);

    GameLoop gameLoop(&audioManager, &renderer, &inputHandler, &player);
    gameLoop.run();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
