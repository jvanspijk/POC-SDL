#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <memory>
#include "Component.h"

class Entity {
public:
    Entity(unsigned int id) : id(id) {}
    unsigned int id;
};
#endif // ENTITY_H
