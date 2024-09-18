#pragma once
#include <string>
#include "EntityManager.h"

class WorldBuilder
{
public:
	WorldBuilder(const EntityManager& mngr);
	void createLevel(std::string level[]);
private:
	void createEntity(int x, int y);
	void createWall(int x, int y);
	EntityManager manager;
};

