#ifndef ICOLORREPRESENTATION_H
#define ICOLORREPRESENTATION_H

#include "RGBA.h"

class IColorRepresentation {
public:
    virtual RGBA toRGBA() const = 0;
    virtual ~IColorRepresentation() = default;
};

#endif
