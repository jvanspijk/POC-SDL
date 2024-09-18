#pragma once
#include "LocationComponent.h"

class BlockingComponent : public EntityComponent
{
public:
	BlockingComponent(int entity, LocationComponent &locComponent);
	LocationComponent locationComponent;	
};

