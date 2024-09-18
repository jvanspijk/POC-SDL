#include "WorldBuilder.h"
#include "BlockingComponent.h"


WorldBuilder::WorldBuilder(const EntityManager& mngr) : manager(mngr) {}

void WorldBuilder::createLevel(std::string level[]) {
    for (int y = 0; y < level->size(); y++) {
        for (int x = 0; x < level[y].size(); x++) {
            switch (level[x][y])
            {
            case '#':
                createWall(x, y);
            default:
                break;
            }

        }
    }
}



void WorldBuilder::createWall(int xLoc, int yLoc) {
    int entity = manager.createEntity();
    LocationComponent locComponent(entity, xLoc, yLoc);
    BlockingComponent component(entity, locComponent);
    manager.addComponent(locComponent);
    manager.addComponent(component);
}

