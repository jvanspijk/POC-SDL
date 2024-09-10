#include "Color.h"
#include "RgbaColorRepresentation.h"
#include "HexColorRepresentation.h"
#include "PredefinedColorRepresentation.h"

// Private constructor
Color::Color(const IColorRepresentation& colorRepresentation) : rgba(colorRepresentation.toRGBA()) {}

// Factory method for RGBA
Color Color::fromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    return Color(RgbaColorRepresentation(r, g, b, a));
}

// Factory method for Hex
Color Color::fromHex(const std::string& hexCode) {
    return Color(HexColorRepresentation(hexCode));
}

// Factory method for Predefined colors
Color Color::fromPredefined(const std::string& name) {
    return Color(PredefinedColorRepresentation(name));
}

// Get RGBA value
RGBA Color::getRGBA() const {
    return rgba;
}
