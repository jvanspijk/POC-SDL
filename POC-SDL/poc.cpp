#include <SDL.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAME_DELAY = 16; // ~60 FPS
const int CIRCLE_RADIUS = 20;
const int CIRCLE_INITIAL_X = CIRCLE_RADIUS;
const int CIRCLE_INITIAL_Y = SCREEN_HEIGHT / 2;
const int CIRCLE_VELOCITY = 3;
const SDL_Color BACKGROUND_COLOR = { 255, 255, 255, 255 }; // White
const SDL_Color CIRCLE_COLOR = { 0, 0, 0, 255 }; // Black

void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Moving Circle",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int x = CIRCLE_INITIAL_X;
    int y = CIRCLE_INITIAL_Y;
    int xVel = CIRCLE_VELOCITY;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        x += xVel;
        if (x - CIRCLE_RADIUS < 0 || x + CIRCLE_RADIUS > SCREEN_WIDTH) {
            xVel = -xVel;
        }

        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, CIRCLE_COLOR.r, CIRCLE_COLOR.g, CIRCLE_COLOR.b, CIRCLE_COLOR.a);
        DrawCircle(renderer, x, y, CIRCLE_RADIUS);

        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
