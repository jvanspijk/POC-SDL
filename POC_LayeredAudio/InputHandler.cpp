#include "InputHandler.h"

InputHandler::InputHandler(AudioManager* audioManager)
    : audioManager(audioManager), isLayer2Active(false) {}

void InputHandler::handleInput(bool& quit, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight, bool& space) {
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
            case SDLK_SPACE: space = !space; break;  
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
