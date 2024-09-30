#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "LayeredAudio.h"
#include <map>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int SQUARE_SIZE = 50;
constexpr int BASE_FREQUENCY = 44100;
constexpr int MAX_CHANNELS = 8; // Number of channels for simultaneous sound effects
const std::string MUSIC_LAYER_1 = "Synthwave3_layer1.ogg";
const std::string MUSIC_LAYER_2 = "Synthwave3_layer2.ogg";

bool isLayer2Enabled = false;  // Toggle state for layer 2
std::map<int, Uint32> fadeOutEndTimes;
int layer2Channel = -1;  // Store the channel for MUSIC_LAYER_2

bool init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Press space to toggle music layer 2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(BASE_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    Mix_AllocateChannels(MAX_CHANNELS);

    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer, Mix_Music* music1, Mix_Chunk* music2) {
    Mix_FreeMusic(music1);
    Mix_FreeChunk(music2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}

Mix_Music* loadMusic(const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
}

Mix_Chunk* loadSoundEffect(const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (sound == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return sound;
}

void FadeIn(int channel, int fadeInSeconds) {
    Mix_Volume(channel, MIX_MAX_VOLUME);  // Restore volume to max
    int fadeInMilliseconds = fadeInSeconds * 1000;
    Mix_FadeInChannel(channel, nullptr, -1, fadeInMilliseconds);
}

void MuteLayer(int channel) {
    Mix_Volume(channel, 0);  // Set volume to 0 (mute)
}

void toggleLayer2() {
    if (isLayer2Enabled) {
        MuteLayer(layer2Channel);
        isLayer2Enabled = false;
        std::cout << "Layer 2 muted." << std::endl;
    }
    else {
        FadeIn(layer2Channel, 2);
        isLayer2Enabled = true;
        std::cout << "Layer 2 fading in." << std::endl;
    }
}

void handleInput(bool& quit, Mix_Chunk* sound) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
            toggleLayer2();
        }
    }
}

void gameLoop(Mix_Chunk* music2, SDL_Renderer* renderer) {
    bool quit = false;

    while (!quit) {
        handleInput(quit, music2);
        // Render code or additional logic can go here
    }
}

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(&window, &renderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    Mix_Music* music1 = loadMusic(MUSIC_LAYER_1);
    Mix_Chunk* music2 = loadSoundEffect(MUSIC_LAYER_2.c_str());

    if (music1 == nullptr || music2 == nullptr) {
        close(window, renderer, music1, music2);
        return -1;
    }

    if (Mix_PlayMusic(music1, -1) == -1) {
        std::cerr << "Failed to play music1: " << Mix_GetError() << std::endl;
    }

    // Play layer 2 in a loop but muted initially using a sound effect channel
    layer2Channel = Mix_PlayChannel(-1, music2, -1);  // Looping the sound indefinitely
    if (layer2Channel == -1) {
        std::cerr << "Failed to play music2: " << Mix_GetError() << std::endl;
    }

    MuteLayer(layer2Channel);  // Mute layer 2 initially

    // Enter game loop
    gameLoop(music2, renderer);

    // Cleanup resources
    close(window, renderer, music1, music2);
    return 0;
}
