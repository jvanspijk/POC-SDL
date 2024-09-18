#pragma once

#include <string>
#include <unordered_map>
#include <typeinfo>

class ComponentTypeRegistry {
public:
    template <typename T>
    static void registerType(const std::string& name) {
        getRegistry()[typeid(T).hash_code()] = name;
    }

    template <typename T>
    static std::string getTypeName() {
        auto& registry = getRegistry();
        auto it = registry.find(typeid(T).hash_code());
        if (it != registry.end()) {
            return it->second;
        }
        return "Unknown Type";
    }

private:
    // Accessor for the static type registry
    static std::unordered_map<std::size_t, std::string>& getRegistry() {
        static std::unordered_map<std::size_t, std::string> registry;
        return registry;
    }
};