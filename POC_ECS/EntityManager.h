#pragma once
#include <vector>
#include <unordered_map>
#include <string> 
#include "EntityComponent.h"
#include "ComponentTypeRegistry.h"
#include "BlockingComponent.h"
#include "DrawableComponent.h"
#include "LocationComponent.h"

class EntityManager
{
public:
	EntityManager() {
		ComponentTypeRegistry::registerType<BlockingComponent>("BlockingComponent");
		ComponentTypeRegistry::registerType<DrawableComponent>("DrawableComponent");
		ComponentTypeRegistry::registerType<LocationComponent>("LocationComponent");
		entities = std::vector<int>(1000);
	}
	std::vector<int> entities;
	std::unordered_map<std::string, std::vector<EntityComponent>> components;

	int createEntity();
	void removeEntity(int entity);

	void addComponent(EntityComponent& component);
};

