#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define SDL_MAIN_HANDLED
#include <string>
#include "IInputBinding.h"
#include <unordered_map>
#include <memory>

class InputManager
{
public:
    static InputManager& getInstance();

    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    void bindAction(const std::string& action, std::unique_ptr<IInputBinding> binding);
    bool isActionPressed(const std::string& action) const;

private:
    InputManager();
    std::unordered_map<std::string, std::unique_ptr<IInputBinding>> actionBindings;

};


#endif //INPUT_MANAGER_H
