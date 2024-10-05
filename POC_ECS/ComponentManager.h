// ComponentManager.h
#ifndef ICOMPONENTMANAGER_H
#define ICOMPONENTMANAGER_H

#include <vector>
#include "Component.h"
#include "Position.h"
#include "Behavior.h"
#include "ComponentType.h"
#include <memory>
#include <unordered_map>

class ComponentManager {
public:
	//every type of component has it's own manager
	void AddComponent(int entity, Component component) {	
		
	}

	//1. 
	void updateBehaviorComponents() {

	}

	//2.
	void updateCollisionComponents() {

	}

	//3.
	void updateRenderComponents() {

	}

	void lateUpdateBehaviorComponents() {
		//Is possible but who cares
	}
private:
	std::vector<Position> _positionComponents;
	std::vector<Behavior> _behaviorComponents;

	std::unordered_map<int, std::vector<Component&>> componentsPerEntity;
};

#endif // ICOMPONENTMANAGER_H