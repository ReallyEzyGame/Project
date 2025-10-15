#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include "entity.h"

inline size_t entityID = 1;
// this vector using the lazy deletion
// the Entity only  dismissed out of vector when the vector allocated
// since each entity is numbered increment so the id is already sorted => binary search for better case
class EntityManager
{
private:
    EntityManager() = default;
    EntityManager(const EntityManager &) = delete;
    ~EntityManager()
    {
        if (instance  != nullptr)
            delete instance;
        instance = nullptr;
    }

    static EntityManager *instance;

public:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    static EntityManager *getInstance();
    size_t createEntity();
    Entity *findEntity(size_t key);
    void deleteEntity(const unsigned int entityID);
};

inline EntityManager *EntityManager::instance = nullptr;

#endif