#ifndef COLOR_H
#define COLOR_H

#include "RGBA.h"
#include "IColorRepresentation.h"
#include <string>

class Color {
private:
    RGBA rgba;

    // Private constructor for internal use
    Color(const IColorRepresentation& colorRepresentation);

public:
    // Factory methods
    static Color fromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
    static Color fromHex(const std::string& hexCode);
    static Color fromPredefined(const std::string& name);

    // Get RGBA value
    RGBA getRGBA() const;
};

#endif // COLOR_H
