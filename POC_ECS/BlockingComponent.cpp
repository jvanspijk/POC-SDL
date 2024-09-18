#include "BlockingComponent.h"
#include <vector>
#include <string>

BlockingComponent::BlockingComponent(int entity, LocationComponent& locComponent) : EntityComponent(entity), locationComponent(locComponent) {};
