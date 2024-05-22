#pragma once
#include "Core.hpp"

namespace Super 
{
static EntityID idCounter = 0;

class EntityManager 
{
public:
    EntityManager() {}

    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;

    EntityID CreateEntity(Entity ent) 
    {
        mEntities.push_back(ent);
        return idCounter++; 
    }

    // Getter for the vector of entities.
    inline std::vector<Entity>& GetAllEntities() { return mEntities; }

private:
    std::vector<Entity> mEntities;

};
}