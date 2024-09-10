#ifndef RGBACOLORREPRESENTATION_H
#define RGBACOLORREPRESENTATION_H

#include "RGBA.h"
#include "IColorRepresentation.h"

class RgbaColorRepresentation : public IColorRepresentation {
private:
    RGBA rgba;

public:
    RgbaColorRepresentation(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255)
        : rgba(r, g, b, a) {}

    RGBA toRGBA() const override {
        return rgba;
    }
};

#endif
