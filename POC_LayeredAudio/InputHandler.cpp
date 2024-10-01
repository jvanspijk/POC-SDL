#include "InputHandler.h"
#include <iostream>

void InputHandler::handleInput(bool& quit, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight, bool& space, float& timeScale) {
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
            case SDLK_PAGEUP: timeScale += 0.1f; std::cout << "time scale: " << timeScale << std::endl; break;
            case SDLK_PAGEDOWN: timeScale -= 0.1f; std::cout << "time scale: " << timeScale << std::endl; break;
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
