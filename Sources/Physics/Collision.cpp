#include "Collision.hpp"

namespace Super 
{
Collision::Collision(EventBus& eventBus, uint32_t width, uint32_t height)
    : System(eventBus)
{
    mSpatialGrid = std::make_unique<SpatialGrid>(width, height, 2, 2);
}

Collision::~Collision() 
{
    
}

void Collision::Update(std::vector<Entity>& entities) 
{
    // Broad Phase - Assigns entities to cells that we iterate over and 
    // check collisions only between entities within the same cell.
    mSpatialGrid->Update(entities, &mCollisionPairs);

    for(const auto& pairs : mCollisionPairs) 
    {
        for(const auto& pair : pairs) 
        {
            if(CheckCollision(pair.A, pair.B))
            {
                pair.A->body.velocity = {0.0f, 0.0f};
            }
        }
    }
}


bool Collision::CheckCollision(Entity* ent1, Entity* ent2) 
{

    // collision x-axis?
    bool collisionX = ent1->bounds.max.x >= ent2->bounds.min.x &&
        ent2->bounds.max.x >= ent1->bounds.min.x;
    // collision y-axis?
    bool collisionY = ent1->bounds.max.y >= ent2->bounds.min.y &&
        ent2->bounds.max.y >= ent1->bounds.min.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

bool Collision::CheckCollision(Entity* ent) 
{

    const uint32_t gridWidth = mSpatialGrid->GetGridWidth();
    const uint32_t gridHeight = mSpatialGrid->GetGridHeight();

    // x-axis collision.
    //
    if(ent->bounds.min.x <= 0.0f)       return true;
    if(ent->bounds.max.x >= gridWidth)  return true;

    // y-axis collision.
    //
    if(ent->bounds.min.y <= 0.0f)       return true;
    if(ent->bounds.max.y >= gridHeight) return true;

    return false;
}

void Collision::HandleCollision(Entity* ent1, Entity* ent2) 
{
    
}

} 