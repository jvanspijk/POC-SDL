#include "Renderer.h"
#include <iostream>

Renderer::Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}

void Renderer::renderPlayer(float x, float y) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect fillRect = { static_cast<int>(x), static_cast<int>(y), 50, 50 };
    SDL_RenderFillRect(renderer, &fillRect);
}

void Renderer::presentScreen() {
    SDL_RenderPresent(renderer);
}
