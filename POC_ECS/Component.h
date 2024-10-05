#ifndef COMPONENT_H
#define COMPONENT_H
#include "ComponentType.h"

class Component {
public:
    void onStart();
    void onUpdate();
    bool active;
};

#endif