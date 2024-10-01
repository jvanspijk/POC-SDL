#include "Renderer.h"
#include <iostream>
#include <cmath>


Renderer::Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::clearScreen(bool applyRainbowEffect, float deltaTime, float bpm) {
    static int colorIndex = 0;
    static float elapsedTime = 0.0f;

    if (applyRainbowEffect) {
        elapsedTime += deltaTime;

        // Change color every beat (based on BPM)        
        const float timePerBeat = 60.0f / bpm;
        const float tolerance = timePerBeat * 0.01f;  // 1% tolerance

        if (elapsedTime >= (timePerBeat - tolerance)) {
            elapsedTime = 0.0f;
            colorIndex = (colorIndex + 1) % 12;
        }

        Uint8 r, g, b;
        setColorByIndex(colorIndex, r, g, b);
        SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    }
    else {
        resetColor();
    }
    SDL_RenderClear(renderer);
}

void Renderer::setColorByIndex(int index, Uint8& r, Uint8& g, Uint8& b) {
    switch (index) {
    case 0: r = 0xFF; g = 0x00; b = 0x00; break;  // Red
    case 1: r = 0x00; g = 0xFF; b = 0x00; break;  // Green
    case 2: r = 0xFF; g = 0xA5; b = 0x00; break;  // Orange
    case 3: r = 0x00; g = 0xFF; b = 0xFF; break;  // Cyan
    case 4: r = 0xFF; g = 0xFF; b = 0x00; break;  // Yellow
    case 5: r = 0x00; g = 0x00; b = 0xFF; break;  // Blue
    case 6: r = 0xFF; g = 0x14; b = 0x93; break;  // Deep Pink
    case 7: r = 0x4B; g = 0x00; b = 0x82; break;  // Indigo
    case 8: r = 0xEE; g = 0x82; b = 0xEE; break;  // Violet
    case 9: r = 0xFF; g = 0x00; b = 0xFF; break;  // Magenta
    case 10: r = 0xAD; g = 0xFF; b = 0x2F; break; // GreenYellow
    case 11: r = 0x7F; g = 0xFF; b = 0xD4; break; // Aquamarine
    }
}


void Renderer::renderPlayer(float x, float y) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect fillRect = { static_cast<int>(x), static_cast<int>(y), 50, 50 };
    SDL_RenderFillRect(renderer, &fillRect);
}

void Renderer::resetColor() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void Renderer::presentScreen() {
    SDL_RenderPresent(renderer);
}

void Renderer::HSVtoRGB(float h, float s, float v, Uint8& r, Uint8& g, Uint8& b) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;
    float r_, g_, b_;

    if (h >= 0 && h < 60) { r_ = c; g_ = x; b_ = 0; }
    else if (h >= 60 && h < 120) { r_ = x; g_ = c; b_ = 0; }
    else if (h >= 120 && h < 180) { r_ = 0; g_ = c; b_ = x; }
    else if (h >= 180 && h < 240) { r_ = 0; g_ = x; b_ = c; }
    else if (h >= 240 && h < 300) { r_ = x; g_ = 0; b_ = c; }
    else { r_ = c; g_ = 0; b_ = x; }

    r = static_cast<Uint8>((r_ + m) * 255);
    g = static_cast<Uint8>((g_ + m) * 255);
    b = static_cast<Uint8>((b_ + m) * 255);
}

void Renderer::renderRainbowEffect(float x, float y, float deltaTime) {
    static float hue = 0.0f;

    // Increment hue based on bpm
    float bpm = 108.0f;
    float hueChangeSpeed = (360.0f / (60000.0f / bpm)); 

    hue += hueChangeSpeed * deltaTime;
    if (hue > 360.0f) hue -= 360.0f;

    Uint8 r, g, b;
    HSVtoRGB(hue, 1.0f, 1.0f, r, g, b);

    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);

    SDL_Rect fillRect = { static_cast<int>(x), static_cast<int>(y), 50, 50 };
    SDL_RenderFillRect(renderer, &fillRect);
}


