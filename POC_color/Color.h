#ifndef COLOR_H
#define COLOR_H

#include "RGBA.h"
#include <string>

class Color {
public:
    RGBA rgba;

    static Color fromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
    static Color fromHex(const std::string& hexCode);
    static Color fromPredefined(const std::string& name);

    Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
    Color(const RGBA& rgba);
};

#endif
