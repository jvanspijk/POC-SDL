#ifndef PREDEFINEDCOLORREPRESENTATION_H
#define PREDEFINEDCOLORREPRESENTATION_H

#include "IColorRepresentation.h"
#include "RGBA.h"
#include <unordered_map>
#include <string>
#include <stdexcept>

class PredefinedColorRepresentation : public IColorRepresentation {
private:
    std::string name;

    static const std::unordered_map<std::string, RGBA> predefinedColors;

public:
    PredefinedColorRepresentation(const std::string& predefinedName) : name(predefinedName) {}

    RGBA toRGBA() const override {
        auto it = predefinedColors.find(name);
        if (it != predefinedColors.end()) {
            return it->second;
        }
        else {
            throw std::invalid_argument("Predefined color not found.");
        }
    }
};

const std::unordered_map<std::string, RGBA> PredefinedColorRepresentation::predefinedColors = {
    {"Black",   RGBA(0, 0, 0)},
    {"Blue",    RGBA(0, 0, 255)},
    {"Clear",   RGBA(0, 0, 0, 0)},
    {"Cyan",    RGBA(0, 255, 255)},
    {"Gray",    RGBA(128, 128, 128)},
    {"Green",   RGBA(0, 255, 0)},
    {"Grey",    RGBA(128, 128, 128)},
    {"Magenta", RGBA(255, 0, 255)},
    {"Red",     RGBA(255, 0, 0)},
    {"White",   RGBA(255, 255, 255)},
    {"Yellow",  RGBA(255, 255, 0)}
};

#endif

