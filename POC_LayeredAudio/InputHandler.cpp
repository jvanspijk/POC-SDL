#include "InputHandler.h"

InputHandler::InputHandler(AudioManager* audioManager)
    : audioManager(audioManager), isLayer2Active(false) {}

void InputHandler::handleInput(bool& quit, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_w: moveUp = true; break;
            case SDLK_s: moveDown = true; break;
            case SDLK_a: moveLeft = true; break;
            case SDLK_d: moveRight = true; break;

            case SDLK_SPACE:
                if (isLayer2Active) {
                    audioManager->fadeOut("layer2", 1); //Hardcoded layer2 is ugly, but it will have to do for now
                    isLayer2Active = false;
                }
                else {
                    audioManager->fadeIn("layer2", 1); 
                    isLayer2Active = true;
                }
                break;
            }
        }
        else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
            case SDLK_w: moveUp = false; break;
            case SDLK_s: moveDown = false; break;
            case SDLK_a: moveLeft = false; break;
            case SDLK_d: moveRight = false; break;
            }
        }
    }
}
