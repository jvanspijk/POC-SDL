#include <iostream>
#include "EntityComponent.h"


EntityComponent::EntityComponent(int entityId) : entity(entityId) {};


EntityComponent::EntityComponent() {
	std::cout << "Warning: default constructor used." << std::endl;
	entity = -1;
}