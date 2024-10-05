#define SDL_MAIN_HANDLED
#include <iostream>
#include <string>
#include "InputManager.h"
#include "SDLInputBinding.h"

void initializeInputBindings()
{
    InputManager& inputManager = InputManager::getInstance();

    inputManager.bindAction("Jump", std::make_unique<SDLInputBinding>("Jump", SDLK_SPACE));
    inputManager.bindAction("MoveLeft", std::make_unique<SDLInputBinding>("MoveLeft", SDLK_a));
    inputManager.bindAction("MoveRight", std::make_unique<SDLInputBinding>("MoveRight", SDLK_d));
    inputManager.bindAction("Crouch", std::make_unique<SDLInputBinding>("Crouch", SDLK_LCTRL));
}

void createEntity() {

}

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        return -1;
    }

    initializeInputBindings();

    SDL_Quit();
}