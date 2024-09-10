#ifndef HEXCOLORREPRESENTATION_H
#define HEXCOLORREPRESENTATION_H

#include "IColorRepresentation.h"
#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class HexColorRepresentation : public IColorRepresentation {
private:
    std::string hex;

public:
    HexColorRepresentation(const std::string& hexCode) : hex(hexCode) {}

    RGBA toRGBA() const override {
        std::regex hexPattern("^#([A-Fa-f0-9]{6})([A-Fa-f0-9]{2})?$");
        std::smatch match;

        if (!std::regex_match(hex, match, hexPattern)) {
            throw std::invalid_argument("Invalid hex code format");
        }

        unsigned int red, green, blue, alpha = 255;

        std::istringstream(match[1].str().substr(0, 2)) >> std::hex >> red;
        std::istringstream(match[1].str().substr(2, 2)) >> std::hex >> green;
        std::istringstream(match[1].str().substr(4, 2)) >> std::hex >> blue;

        if (match.length(2) == 2) {
            std::istringstream(match[2].str()) >> std::hex >> alpha;
        }

        return RGBA(red, green, blue, alpha);
    }
};

#endif
