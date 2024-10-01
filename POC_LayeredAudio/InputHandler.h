#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include "AudioManager.h"

class InputHandler {
public:
    void handleInput(bool& quit, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight, bool& space, float& timeScale);

private:
    AudioManager* audioManager;
    bool isLayer2Active;
};

#endif // INPUT_HANDLER_H
