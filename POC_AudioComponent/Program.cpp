#include <iostream>
#include "OpenALPlayer.h"

int main() {
    OpenALPlayer* player = new OpenALPlayer();
    if (!player->Load("Synthwave_layer1.ogg")) {
        delete player;
        return -1; // Exit if loading failed
    }

    player->Play(1);

    while (true) { // Main loop for updating stream
        player->Update();
        // Add a way to break out of this loop (e.g., based on user input)
    }

    delete player; // Clean up
    return 0;
}

