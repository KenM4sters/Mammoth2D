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

    void CreateEntity(Entity ent) 
    {
        ent.id = idCounter++;
        mEntities.push_back(ent); 
    }

    // Getter for the vector of entities.
    inline std::vector<Entity>& GetAllEntities() { return mEntities; }

private:
    std::vector<Entity> mEntities;

};
}