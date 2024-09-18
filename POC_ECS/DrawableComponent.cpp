#include "DrawableComponent.h"

DrawableComponent::DrawableComponent(int entity, char charToRender, int layer) : EntityComponent(entity), icon(charToRender), zIndex(layer) {};
