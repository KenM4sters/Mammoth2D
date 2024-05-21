#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Physics.hpp"

namespace Super 
{
void Physics::Update(std::vector<Entity>& entities) 
{
    for(auto& entity : entities) 
    {
        UpdateMotion(entity);
    }
}

void Physics::UpdateMotion(Entity& entity) 
{
    auto& p = entity.body;
    
    p.force += glm::vec2(0.0f, G);

    const glm::vec2 acceleration = p.force * p.inverseMass;

    p.velocity += acceleration;

    entity.transform.position += glm::vec2(p.velocity.x, -p.velocity.y);
    entity.bounds.max += glm::vec2(p.velocity.x, -p.velocity.y);
    entity.bounds.min += glm::vec2(p.velocity.x, -p.velocity.y);

    UpdateTransformMatrix(entity);

    ResetMotion(entity);

}

void Physics::ResetMotion(Entity& entity) 
{
    entity.body.force = {0.0f, 0.0f};
}

void Physics::UpdateTransformMatrix(Entity& entity) 
{
    entity.transform.modelMatrix = glm::mat4(1.0f);
    entity.transform.modelMatrix = glm::translate(entity.transform.modelMatrix, glm::vec3(entity.transform.position, 0.0f));
    entity.transform.modelMatrix = glm::scale(entity.transform.modelMatrix, glm::vec3(entity.transform.scale, 1.0f));
}

}