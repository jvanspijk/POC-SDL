#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "controlGameSpeed.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SQUARE_SIZE = 50;
const float SPEED = 200.0f;  // Speed in pixels per second (adjust as needed)
const float BASE_TIMESCALE = 1.0f;
const int BASE_FREQUENCY = 44100;

bool init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Use Page Up and Page Down to control time scale - reset with Home",
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

    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer, Mix_Chunk* sound) {
    Mix_FreeChunk(sound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}

Mix_Chunk* loadSoundEffect(const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (sound == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return sound;
}


void render(SDL_Renderer* renderer, float x, float y) {
    clearScreen(renderer);
    renderPlayer(renderer, x, y);
    SDL_RenderPresent(renderer);
}

void clearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}

void renderPlayer(SDL_Renderer* renderer, float x, float y)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect fillRect = { static_cast<int>(x), static_cast<int>(y), SQUARE_SIZE, SQUARE_SIZE };
    SDL_RenderFillRect(renderer, &fillRect);
}

void handleInput(bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight, bool& quit, Mix_Chunk* sound, float& timeScale) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        handleKeyPress(e, moveUp, moveDown, moveLeft, moveRight);
        handleKeyRelease(e, moveUp, moveDown, moveLeft, moveRight);
        handleLeftClick(e, sound);
        handleTimeScale(e, timeScale);
    }
}

void handleKeyPress(SDL_Event& e, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_w: moveUp = true; break;
        case SDLK_s: moveDown = true; break;
        case SDLK_a: moveLeft = true; break;
        case SDLK_d: moveRight = true; break;
        }
    }
}

void handleKeyRelease(SDL_Event& e, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight)
{
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_w: moveUp = false; break;
        case SDLK_s: moveDown = false; break;
        case SDLK_a: moveLeft = false; break;
        case SDLK_d: moveRight = false; break;
        }
    }
}

void handleLeftClick(SDL_Event& e, Mix_Chunk* sound)
{
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

void handleTimeScale(SDL_Event& e, float& timeScale) {
    const float increment = 0.5f;
    const float minTimeScale = 0.1f;
    const float maxTimeScale = 5.0f;
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_PAGEDOWN:
            timeScale = std::max(minTimeScale, timeScale - increment);
            adjustAudioFrequency(timeScale);
            break;
        case SDLK_PAGEUP:
            timeScale = std::min(maxTimeScale, timeScale + increment);  // Speed up (capped to prevent negative speed)
            adjustAudioFrequency(timeScale);
            break;
        case SDLK_HOME:
            timeScale = BASE_TIMESCALE;  // Reset speed
            adjustAudioFrequency(timeScale);
            break;
        }        
    }
}

void adjustAudioFrequency(float timeScale) {
    Mix_CloseAudio();
    int newFrequency = static_cast<int>(BASE_FREQUENCY * timeScale);
    if (Mix_OpenAudio(newFrequency, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to adjust audio frequency! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void updatePosition(float& x, float& y, bool moveUp, bool moveDown, bool moveLeft, bool moveRight, float deltaTime) {
    if (moveUp && y > 0) y -= SPEED * deltaTime;
    if (moveDown && y < SCREEN_HEIGHT - SQUARE_SIZE) y += SPEED * deltaTime;
    if (moveLeft && x > 0) x -= SPEED * deltaTime;
    if (moveRight && x < SCREEN_WIDTH - SQUARE_SIZE) x += SPEED * deltaTime;
}

void gameLoop(Mix_Chunk* sound, SDL_Renderer* renderer)
{
    float x = SCREEN_WIDTH / 2 - SQUARE_SIZE / 2;
    float y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;

    bool quit = false;
    bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

    // Track time for deltaTime
    Uint32 lastFrameTime = SDL_GetTicks();
    float timeScale = BASE_TIMESCALE;

    while (!quit) {
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f * timeScale;;  // Convert to seconds
        lastFrameTime = currentFrameTime;


        handleInput(moveUp, moveDown, moveLeft, moveRight, quit, sound, timeScale);
        updatePosition(x, y, moveUp, moveDown, moveLeft, moveRight, deltaTime);
        render(renderer, x, y);
    }
}

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(&window, &renderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    Mix_Chunk* sound = loadSoundEffect("gunshot.wav");
    if (sound == nullptr) {
        close(window, renderer, sound);
        return -1;
    }

    gameLoop(sound, renderer);

    close(window, renderer, sound);
    return 0;
}
