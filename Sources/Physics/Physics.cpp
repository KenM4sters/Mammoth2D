#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Physics.hpp"
#include "Logging.hpp"

namespace Super 
{
void Physics::Update(std::vector<Entity>& entities) 
{

    mEventBus.Subscribe(this, &Physics::SolveImpulse);

    for(auto& entity : entities) 
    {
        if(entity.flags & EntityFlags::IS_RIGID) 
        {
            UpdateMotion(entity);
        }
        else {
            continue;
        }
    }
}

void Physics::UpdateMotion(Entity& entity) 
{
    auto& p = entity.body;
    
    p.force += glm::vec2(0.0f, G);

    const glm::vec2 acceleration = p.force * p.inverseMass;

    p.velocity += acceleration;

    entity.tx.position += glm::vec2(p.velocity.x, -p.velocity.y);

    ResetMotion(entity);

}

void Physics::ResetMotion(Entity& entity) 
{
    entity.body.force = {0.0f, 0.0f};
}

void Physics::SolveImpulse(CollisionEvent* event)
{
    event->mEntityA->body.velocity = {0.0f, 0.0f};
    event->mEntityB->body.velocity = {0.0f, 0.0f};

    // const auto& A = event->mEntityA;
    // const auto& B = event->mEntityB;
    // const auto& penetration = event->penetration; 
    // const auto& N = event->normal; 

    // const glm::vec2 rv = B->body.velocity - A->body.velocity;
    // float velAlongNormal = glm::dot(rv, event->normal);

    // if(velAlongNormal > 0) 
    // {
    //     return;
    // }

    // const float e = std::min(A->body.restitution, B->body.restitution);

    // float j = -(1 + e) * velAlongNormal;
    // j*= A->body.inverseMass + B->body.inverseMass;

    // glm::vec2 impulse = j * event->normal;


    // // LOG_VEC2(event->normal, "norm");


    // A->body.velocity -= A->body.inverseMass * impulse;
    // B->body.velocity += B->body.inverseMass * impulse;
    
}

}