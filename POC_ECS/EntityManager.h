#pragma once
#include <vector>
#include "Entity.h"

class EntityManager
{
public:
	void AddEntity();
	Entity& GetEntity(int id);
private:
	std::vector<uint32_t> _entities; //Limit of 4,294,967,295 entities
};

