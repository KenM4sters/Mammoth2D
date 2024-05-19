#pragma once
#include "SpatialGrid.hpp"
#include "Scene/System.hpp"

namespace Super 
{
class Collision : public System
{
public:
    Collision(uint32_t width, uint32_t height);
    ~Collision();

    virtual void Update(std::vector<Entity>& entities) override;

private:

    bool CheckCollision(Entity* ent1, Entity* ent2);

    void HandleCollision(Entity* ent1, Entity* ent2);

    std::unique_ptr<SpatialGrid> mSpatialGrid = nullptr;
};
}
