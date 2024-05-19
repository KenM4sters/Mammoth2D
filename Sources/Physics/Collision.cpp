#include "Collision.hpp"

namespace Super 
{
Collision::Collision(uint32_t width, uint32_t height) 
{
    mSpatialGrid = std::make_unique<SpatialGrid>(width, height, 2, 2);
}

Collision::~Collision() 
{
    
}

void Collision::Update(std::vector<Entity>& entities) 
{
    mSpatialGrid->Update(entities);

    for(auto& cell : mSpatialGrid->GetMap()) 
    {
        auto& v = cell.second;
        for(int i = 0; i < v.size(); i++) 
        {
            for(int j = 0; j < v.size(); j++) 
            {
                if(i == j) continue;
                if(CheckCollision(v[i], v[j])) 
                {
                    if(v[i]->flags & EntityFlags::HAS_MOTION) v[i]->flags &= ~EntityFlags::HAS_MOTION;
                    if(v[j]->flags & EntityFlags::HAS_MOTION) v[j]->flags &= ~EntityFlags::HAS_MOTION;
                } 
            }
        }
    }
}


bool Collision::CheckCollision(Entity* ent1, Entity* ent2) 
{
    const int w1 = ent1->bounds.size.x;
    const int w2 = ent2->bounds.size.x;

    const int h1 = ent1->bounds.size.y;
    const int h2 = ent2->bounds.size.y;

    const glm::vec2& p1 = ent1->transform.position;
    const glm::vec2& p2 = ent2->transform.position;

    // collision x-axis?
    bool collisionX = p1.x + h1 >= p2.x &&
        p2.x + w2 >= p1.x;
    // collision y-axis?
    bool collisionY = p1.y + h1 >= p2.y &&
        p2.y + h2 >= p1.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

void Collision::HandleCollision(Entity* ent1, Entity* ent2) 
{
    
}

} 