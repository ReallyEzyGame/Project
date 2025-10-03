#include "entityManager.h"

EntityManager* EntityManager::getInstance()
{
    if (instance ==  nullptr) {
        instance = new EntityManager();
    }
    return instance;
}
size_t EntityManager::createEntity()
{
    std::unique_ptr<Entity> e = std::make_unique<Entity>();
    if (e == nullptr)
        std::runtime_error("Failed to Allocate for Entity");

    Entity *raw = e.get();
    raw->id = entityID++;
    entities.emplace_back(move(e));

    return raw->id;
}
Entity *EntityManager::findEntity(size_t key)
{
    int l = 0, r = entities.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (entities[mid]->id < key)
            l = mid + 1;
        else if (entities[mid]->id > key)
            r = mid - 1;
        else
        {
            if (!entities[mid]->deleted)
                return entities[mid].get();
            break;
        }
    }
    return nullptr;
}
void EntityManager::deleteEntity(const unsigned int entityID)
{
    int l = 0, r = entities.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (entities[mid]->id < entityID)
            l = mid + 1;
        else if (entities[mid]->id > entityID)
            r = mid - 1;
        else
        {
            entities[mid]->deleted = true;
            break;
        }
    }
    return;
}
