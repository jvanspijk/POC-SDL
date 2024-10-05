#pragma once
#include "IInputBinding.h"
#include <SDL2/SDL.h>

class SDLInputBinding : public IInputBinding
{
public:
    SDLInputBinding(const std::string& name, SDL_Keycode keycode)
        : key(keycode)
    {
        actionName = name;
    }

    bool isActionTriggered() const override
    {
        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        return keystate[SDL_GetScancodeFromKey(key)];
    }

private:
    SDL_Keycode key;
};

