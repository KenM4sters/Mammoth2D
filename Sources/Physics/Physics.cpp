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
    const auto& A = event->mEntityA;
    const auto& B = event->mEntityB;
    const auto& penetration = event->penetration; 
    const auto& N = event->normal; 

    glm::vec2 rv = B->body.velocity - A->body.velocity;
    float velAlongNormal = glm::dot(rv, event->normal);

    const float e = glm::min(A->body.restitution, B->body.restitution);

    float j = -(1 + e) * velAlongNormal;
    j /= (A->body.inverseMass + B->body.inverseMass);  // Divide by sum of inverse masses

    glm::vec2 impulse = j * event->normal;

    A->body.velocity -= A->body.inverseMass * impulse;
    B->body.velocity += B->body.inverseMass * impulse;

    // Friction calculation.
    //
    glm::vec2 tangent = rv - glm::dot(rv, event->normal) * event->normal;

    // Check if the tangent vector is a zero vector.
    //
    if (glm::length(tangent) < 1e-6) 
    {
        tangent = glm::vec2(0.0f, 0.0f);
    } 
    else {
        tangent = glm::normalize(tangent);
    }

    float jt = -glm::dot(rv, tangent);

    jt /= (A->body.inverseMass + B->body.inverseMass);

    float mu = std::sqrt(A->body.staticFrictionCoefficient * A->body.staticFrictionCoefficient +
                         B->body.staticFrictionCoefficient * B->body.staticFrictionCoefficient);

    glm::vec2 frictionImpulse{0.0f};
    if(glm::abs(jt) < j * mu) 
    {
        frictionImpulse = jt * tangent;
    } 
    else {
        float dynamicFriction = std::sqrt(A->body.dynamicFrictionCoefficient * A->body.dynamicFrictionCoefficient 
                                + B->body.dynamicFrictionCoefficient * B->body.dynamicFrictionCoefficient);
        frictionImpulse = j * tangent * dynamicFriction;
    }

    A->body.velocity -= A->body.inverseMass * frictionImpulse;
    B->body.velocity += B->body.inverseMass * frictionImpulse;

    // Position correction aginst floating point errors (causing objects to sink). 
    // (comment this function out to see what I mean...)
    CorrectPenetration(event);
}

void Physics::CorrectPenetration(CollisionEvent* event) 
{
    auto& A = event->mEntityA;
    auto& B = event->mEntityB;

    const float percent = 0.2; // usually 20% to 80% 
    const float slop = 0.1; // usually 0.01 to 0.1 

    glm::vec2 correction = std::max(event->penetration - slop, 0.0f ) * (A->body.inverseMass + B->body.inverseMass) * percent * event->normal;

    A->tx.position -= A->body.inverseMass * correction;
    B->tx.position += B->body.inverseMass * correction;
}

}