#pragma once
#include "EntityComponent.h"

class DrawableComponent : EntityComponent {
public:
	char icon;
	int zIndex;
	DrawableComponent(int entity, char charToRender, int layer);
};

