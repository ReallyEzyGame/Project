#ifndef ENTITY_H
#define ENTITY_H
#include "component.h"

class EntityManager;

class Entity
{ 
public:
    bool deleted = false; // lazy Deletion, the entity only delete out of the array when the new allocate occurs
    size_t id;
    int z_index;
    std::string name;
    
    std::vector<std::unique_ptr<Component>> components;

    Entity() = default;
    template <typename T, typename... Argv>
    T *addComponent(Argv &&...args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derived from Component");
        std::unique_ptr<T> ptr = std::make_unique<T>(this,std::forward<Argv>(args)...);
        T *raw = ptr.get();
        components.emplace_back(move(ptr));

        // raw->init();              // add to the component later on
        return raw;
    }
    template <typename T>
    T *getComponent()
    {
        size_t key = ECS::getComponentID<T>();
        for (std::unique_ptr<Component> &component : components)
        {
            if (key == component->getID())
            {
                return dynamic_cast<T *>(component.get());
            }
        }
        return nullptr;
    }
    template <typename T>
    bool hasComponent()
    {
        size_t key = ECS::getComponentID<T>();
        for (std::unique_ptr<Component> &component : components)
        {
            if (key == component->getID())
            {
                return true;
            }
        }
        return false;
    }
    template <typename T>
    void removeComponent()
    {
        size_t key = ECS::getComponentID<T>();
        for (std::unique_ptr<Component> &component : components)
        {
            if (key == component->getID())
            {
                swap(component, components.back());
                components.pop_back();
                break;
            }
        }
    }

};


#endif