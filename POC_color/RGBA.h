#ifndef RGBA_H
#define RGBA_H

struct RGBA {
    unsigned int r, g, b, a;

    RGBA(unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

#endif

