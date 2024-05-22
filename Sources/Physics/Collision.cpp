#include "Collision.hpp"
#include "Events/Event.hpp"
#include <set>

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

    UpdateCollisionPairs();

    for(auto& pairs : mCollisionPairs) 
    {
        for(auto& pair : pairs) 
        {
            void* manifold = CheckCollision(pair);

            if(manifold) 
            {
                mEventBus.Publish(new CollisionEvent(reinterpret_cast<Manifold*>(manifold)));
            }
        }
    }
}

void Collision::UpdateCollisionPairs() 
{
    std::set<CollisionPair> uniquePairs{};
}   


void* Collision::CheckCollision(CollisionPair pair) 
{
    const auto& A = pair.A;
    const auto& B = pair.B;
    const auto& aMinX = A->tx.position.x;
    const auto& bMinX = B->tx.position.x;
    const auto& aMaxX = A->tx.position.x + A->tx.scale.x;
    const auto& bMaxX = B->tx.position.x + B->tx.scale.x;

    const auto& aMinY = A->tx.position.y;
    const auto& bMinY = B->tx.position.y;
    const auto& aMaxY = A->tx.position.y + A->tx.scale.y;
    const auto& bMaxY = B->tx.position.y + B->tx.scale.y;

    // Firstly, check that the two objects have collided using an SAT
    // (Single Axis Theorem) test. If they have collided,
    // then proceed to declaring and defining a new Manifold object.
    //
    // collision x-axis?
    bool collisionX = aMaxX >= bMinX &&
        bMaxX >= aMinX;
    // collision y-axis?
    bool collisionY = aMaxY >= bMinY &&
        bMaxY >= aMinY;

    if(!collisionX | !collisionY ) 
    {
        return nullptr;
    }

    const glm::vec2 p = B->tx.position - A->tx.position;

    const float aExtent = ((A->tx.position.x + A->tx.scale.x) - A->tx.position.x) / 2;
    const float bExtent = ((B->tx.position.x + B->tx.scale.x) - B->tx.position.x) / 2;

    const float xOverlap = aExtent + bExtent - std::abs(p.x);

    glm::vec2 collisionNormal{0.0f};
    float penetration{0.0f};


    if(xOverlap > 0) 
    {
        const float aExtent = ((A->tx.position.y + A->tx.scale.y) - A->tx.position.y) / 2;
        const float bExtent = ((B->tx.position.y + B->tx.scale.y) - B->tx.position.y) / 2;

        float yOverlap = aExtent + bExtent - std::abs(p.y);

        if(yOverlap > 0) 
        {
            if(xOverlap > yOverlap) 
            {
                if(p.x < 0) 
                {
                    collisionNormal = glm::vec2(-1, 0);
                } else 
                {
                    collisionNormal = glm::vec2(0, 0);
                }
                penetration = xOverlap;
            } else 
            {
                if(p.y < 0) 
                {
                    collisionNormal = glm::vec2(0, 1);
                } else 
                {
                    collisionNormal = glm::vec2(0, -1);
                }
                penetration = yOverlap;
            }
        }
    }

    return new Manifold{pair, penetration, collisionNormal};
}

bool Collision::CheckCollision(Entity* ent) 
{

    const uint32_t gridWidth = mSpatialGrid->GetGridWidth();
    const uint32_t gridHeight = mSpatialGrid->GetGridHeight();

    const auto& minX = ent->tx.position.x;
    const auto& maxX = ent->tx.position.x + ent->tx.scale.x;

    const auto& minY = ent->tx.position.y;
    const auto& maxY = ent->tx.position.y + ent->tx.scale.y;

    // x-axis collision.
    //
    if(minX <= 0.0f)       return true;
    if(maxX >= gridWidth)  return true;

    // y-axis collision.
    //
    if(minY <= 0.0f)       return true;
    if(maxY >= gridHeight) return true;

    return false;
}

void Collision::HandleCollision(Entity* ent1, Entity* ent2) 
{
    
}

} 