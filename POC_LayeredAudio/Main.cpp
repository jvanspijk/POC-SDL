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

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        return -1;
    }

    Renderer renderer(window);
    const int amountOfAudioChannels = 8;
    const int baseFrequency = 44100;

    AudioManager audioManager(amountOfAudioChannels, baseFrequency);
    
    //SDL mixer does not support playing two music tracks simultaneosly
    //We load it in as 2 soundeffects as a hacky workaround
    audioManager.loadSoundEffect("Synthwave_layer1.ogg", "layer1");
    audioManager.loadSoundEffect("Synthwave_layer2.ogg", "layer2");
    audioManager.playSoundEffect("layer1", -1);
    audioManager.playSoundEffect("layer2", -1);
    audioManager.mute("layer1");
    audioManager.mute("layer2");
    audioManager.fadeIn("layer1", 2.0f); //Fade in does not work, neither does fadeout..

    //Ugly to pass audiomanager as a dependency for inputhandler but it will have to do for now
    InputHandler inputHandler(&audioManager);

    const int playerStartX = 400;
    const int playerStartY = 300;
    const float playerSpeed = 4.0f;
    Player player(playerStartX, playerStartY, playerSpeed);

    //Passing raw pointers... yeah.
    GameLoop gameLoop(&audioManager, &renderer, &inputHandler, &player);
    gameLoop.run();

    audioManager.close();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
