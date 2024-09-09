#pragma once

void handleKeyPress(SDL_Event& e, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight);

void handleLeftClick(SDL_Event& e, Mix_Chunk* sound);

void renderPlayer(SDL_Renderer* renderer, float x, float y);

void gameLoop(Mix_Chunk* sound, SDL_Renderer* renderer);

void clearScreen(SDL_Renderer* renderer);

void handleKeyRelease(SDL_Event& e, bool& moveUp, bool& moveDown, bool& moveLeft, bool& moveRight);
