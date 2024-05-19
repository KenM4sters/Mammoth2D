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
        if(entity.flags & EntityFlags::HAS_MOTION) 
        {
            UpdateMotion(entity);
        }
    }
}

void Physics::UpdateMotion(Entity& entity) 
{
    auto& m = entity.motion;

    ResetMotion(entity);

    m.acceleration += glm::vec2(0.0f, G);
    m.velocity += m.acceleration;
    entity.transform.position += glm::vec2(m.velocity.x, -m.velocity.y);

    UpdateTransformMatrix(entity);

}

void Physics::ResetMotion(Entity& entity) 
{
    entity.motion.acceleration = glm::vec2(0.0f);
}

void Physics::UpdateTransformMatrix(Entity& entity) 
{
    entity.transform.modelMatrix = glm::mat4(1.0f);
    entity.transform.modelMatrix = glm::translate(entity.transform.modelMatrix, glm::vec3(entity.transform.position, 0.0f));
    entity.transform.modelMatrix = glm::scale(entity.transform.modelMatrix, glm::vec3(entity.transform.scale, 1.0f));
}

}