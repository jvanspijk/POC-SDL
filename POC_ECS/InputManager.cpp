#include "InputManager.h"

InputManager::InputManager() 
{
    actionBindings.reserve(16); //16 for now, we need a constexpr with the used keys
}

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::bindAction(const std::string& action, std::unique_ptr<IInputBinding> binding)
{
    //TODOL Throw exception when already exists!
    actionBindings[action] = std::move(binding);
}

bool InputManager::isActionPressed(const std::string& action) const
{
    auto it = actionBindings.find(action);
    if (it != actionBindings.end())
    {
        return it->second->isActionTriggered();
    }
    return false;
}