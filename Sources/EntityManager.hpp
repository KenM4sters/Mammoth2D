#include "Entity.hpp"



namespace Super 
{
static EntityID idCounter = 0;

class EntityManager 
{
public:
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;

    static void Destroy() 
    {
        for(const auto& entity : mEntities) 
        {
            delete entity;
        }
    }

    static Entity* CreateEntity() 
    {
        Entity* ent = new Entity{};
        ent->id = idCounter++;
        mEntities.push_back(ent);

        return ent;
    }

private:
    EntityManager() {}

    static std::vector<Entity*> mEntities;

};
}