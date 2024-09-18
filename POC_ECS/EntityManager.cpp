#include <algorithm>
#include "EntityManager.h"




int EntityManager::createEntity() {
    int entity;

    if (entities.empty()) {
        entity = 0;
    }
    else {
        entity = entities.back() + 1;
    }

    entities.push_back(entity);
    return entity;
}

void EntityManager::removeEntity(int entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void EntityManager::addComponent(EntityComponent& component) {
    std::string typeName = ComponentTypeRegistry::getTypeName<decltype(component)>();
    if (components.find(typeName) != components.end()) {
        components[typeName] = std::vector<EntityComponent>(10000);
    }

    components[typeName][component.entity] = component;
}

