#pragma once
#include "EntityComponent.h"

class LocationComponent : public EntityComponent
{
public:
    int x, y;

    LocationComponent(int entity, int xLoc, int yLoc);
};
