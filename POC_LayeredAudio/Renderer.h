#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void clearScreen(bool applyRainbowEffect, float deltaTime);
    void renderPlayer(float x, float y);
    void presentScreen();
    void renderRainbowEffect(float x, float y, float deltaTime);
    void resetColor();

private:
    void HSVtoRGB(float h, float s, float v, Uint8& r, Uint8& g, Uint8& b);
    void setColorByIndex(int index, Uint8& r, Uint8& g, Uint8& b);
    SDL_Renderer* renderer;
};

#endif // RENDERER_H
