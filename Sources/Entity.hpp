#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <vector>
#include "Buffer.hpp"

namespace Super 
{
using EntityID = uint16_t;

typedef enum entityflags 
{
    ACTIVE              = 1,
    PLAYER_CONTROLLED   = 1 << 1,
    IS_RIGID            = 1 << 2,
    HAS_MOTION          = 1 << 3,
    HAS_HEALTH          = 1 << 4,    
} EntityFlags;


typedef struct transform 
{
    glm::vec2 position;
    glm::vec2 scale;
    glm::mat3 modelMatrix;
} Transform;

typedef struct physics 
{
    glm::vec2 velocity;
    glm::vec2 acceleration;
} Physics;

typedef struct entity 
{
    EntityID id;
    int flags;
    glm::vec3 color;
    Transform transform;
    Physics physics;
} Entity;

}