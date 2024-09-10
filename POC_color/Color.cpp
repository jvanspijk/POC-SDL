#include "Color.h"
#include "HexColorRepresentation.h"
#include "PredefinedColorRepresentation.h"

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
    : rgba(r, g, b, a) {}

Color::Color(const RGBA& rgba)
    : rgba(rgba) {}

Color Color::fromRGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    return Color(r, g, b, a);
}

Color Color::fromHex(const std::string& hexCode) {
    HexColorRepresentation hexColorRepresentation(hexCode);
    RGBA rgba = hexColorRepresentation.toRGBA();
    return Color(rgba);
}

Color Color::fromPredefined(const std::string& name) {
    PredefinedColorRepresentation predefinedColorRepresentation(name);
    RGBA rgba = predefinedColorRepresentation.toRGBA();
    return Color(rgba);
}
