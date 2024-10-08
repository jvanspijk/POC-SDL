#include <iostream>
#include "Color.h"

int main() {
    // Create color from RGBA
    Color rgbaColor = Color::fromRGBA(255, 0, 0, 128);
    RGBA rgba1 = rgbaColor.rgba;
    std::cout << "RGBA from RGBA: [" << rgba1.r << ", " << rgba1.g << ", " << rgba1.b << ", " << rgba1.a << "]" << std::endl;

    // Create color from Hex
    Color hexColor = Color::fromHex("#00ff00ff");
    RGBA rgba2 = hexColor.rgba;
    std::cout << "RGBA from Hex: [" << rgba2.r << ", " << rgba2.g << ", " << rgba2.b << ", " << rgba2.a << "]" << std::endl;

    // Create color from predefined color
    Color predefinedColor = Color::fromPredefined("Blue");
    RGBA rgba3 = predefinedColor.rgba;
    std::cout << "RGBA from predefined 'Blue': [" << rgba3.r << ", " << rgba3.g << ", " << rgba3.b << ", " << rgba3.a << "]" << std::endl;

    //Invalid colors:
    //Color rgbaColor2 = Color::fromRGBA(-20, 0, 0, 128);
    //std::cout << "RGBA from RGBA2: [" << rgbaColor2.rgba.r << ", " << rgbaColor2.rgba.g << ", " << rgbaColor2.rgba.b << ", " << rgbaColor2.rgba.a << "]" << std::endl;
    //Color hexColor2 = Color::fromHex("lol");
    //Color predefinedColor2 = Color::fromPredefined("Bellow");

    return 0;
}
