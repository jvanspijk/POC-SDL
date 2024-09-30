#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void clearScreen();
    void renderPlayer(float x, float y);
    void presentScreen();

private:
    SDL_Renderer* renderer;
};

#endif // RENDERER_H
