#ifndef COMPONENT_H
#define COMPONENT_H
#include "ComponentType.h"

class Component {
public:
    ComponentType type;

    Component() {
        hasChanged = false;
    }

    bool hasChanged; //This will be handy for some components to skip other components like the renderer    
};

#endif