#include <iostream>
#include "OpenALPlayer.h"

int main() {
    //TODO: fix concurrency bug
    //Maybe by centralizing the player and context in the audio manager?
    //Something is shared between player1 and player2 that shouldn't be
    OpenALPlayer* player = new OpenALPlayer();
    if (!player->Load("Synthwave_layer1.ogg")) {
        delete player;
        return -1;
    }

    OpenALPlayer* player2 = new OpenALPlayer();
    if (!player2->Load("Synthwave_layer2.ogg")) {
        delete player2;
        return -1;
    }

    player->Play(1);
    player2->Play(1);
    while (true) {
        player->Update();
        player2->Update();
    }

    delete player;
    delete player2;
    return 0;
}

