#ifndef SYSTEM_H
#define SYSTEM_H

#include "ComponentManager.h"

class System {
protected:
    ComponentManager& componentManager;

public:
    explicit System(ComponentManager& manager) : componentManager(manager) {}
    virtual void update() = 0;
};

#endif // SYSTEM_H