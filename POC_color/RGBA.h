#ifndef RGBA_H
#define RGBA_H

#include <stdexcept>

struct RGBA {
    unsigned int r, g, b, a;

    RGBA(unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int alpha = 255) {
        if (red > 255 || green > 255 || blue > 255 || alpha > 255) {
            throw std::invalid_argument("Color component values must be between 0 and 255");
        }
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
};

#endif

