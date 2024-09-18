#include <iostream>
#include <string>
#include "WorldBuilder.h"
#include "EntityManager.h"

void runGameLoop()
{
    std::cin;
}

void run(std::string level[])
{
    EntityManager manager;
    WorldBuilder builder(manager);
    builder.createLevel(level);

    runGameLoop();
}

//TODO: stuck at 9 mins of components basis
int main()
{
    std::cout << "test1" << std::endl;
    std::string level[] = {
        "#######",
        "#@----#",
        "#####-#",
        "#-----#",
        "#-#####",
        "#-----#",
        "#######"
    };
    run(level);
}