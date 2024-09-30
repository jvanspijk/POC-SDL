#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "AudioManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Player.h"

class GameLoop {
public:
    GameLoop(AudioManager* audioManager, Renderer* renderer, InputHandler* inputHandler, Player* player);
    void run();

private:
    AudioManager* audioManager;
    Renderer* renderer;
    InputHandler* inputHandler;
    Player* player;
};

#endif // GAME_LOOP_H
