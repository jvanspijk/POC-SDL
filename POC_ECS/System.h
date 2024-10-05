#ifndef SYSTEM_H
#define SYSTEM_H

#include "ComponentManager.h"

class System {
protected:
    IComponentManager& componentManager;

public:
    explicit System(IComponentManager& manager) : componentManager(manager) {}
    virtual void update() = 0;
};

#endif // SYSTEM_H