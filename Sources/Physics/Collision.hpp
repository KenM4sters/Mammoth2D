#pragma once
#include "SpatialGrid.hpp"
#include "Scene/System.hpp"

namespace Super 
{
class Collision : public System
{
public:
    Collision(EventBus& eventBus, uint32_t width, uint32_t height);
    ~Collision();

    virtual void Update(std::vector<Entity>& entities) override;
    
private:

    // Testt whether two entities have collided or not and returns either false or true.
    bool CheckCollision(Entity* ent1, Entity* ent2);

    // Tests whether an entity has collided with the window boundaries and returns either true or false.
    bool CheckCollision(Entity* ent1);

    // TODO: Should trigger some kind of collision event.
    void HandleCollision(Entity* ent1, Entity* ent2);

    std::unique_ptr<SpatialGrid> mSpatialGrid = nullptr;

    std::vector<std::vector<CollisionPair>> mCollisionPairs{};
};
}
