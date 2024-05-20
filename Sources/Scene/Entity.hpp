#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <vector>

namespace Super 
{
using EntityID = uint16_t;

typedef enum entityflags 
{
    ACTIVE              = 1,
    IS_PLAYER           = 1 << 1,
    IS_RIGID            = 1 << 2,
    HAS_MOTION          = 1 << 3,
    HAS_HEALTH          = 1 << 4,
    IS_BULLET           = 1 << 5,
    IS_ENEMY            = 1 << 6,
    IS_PLATFORM         = 1 << 7,
} EntityFlags;


typedef struct transform 
{
    alignas(8) glm::vec2 position{0.0f};
    alignas(8) glm::vec2 scale{1.0f};
    alignas(16) glm::mat4 modelMatrix{1.0f};
} Transform;

typedef struct rigidbody 
{
    float inverseMass;
    float denisty;
    float restitution;
    glm::vec2 force;
    glm::vec2 velocity;
} RigidBody;

typedef struct bounds 
{
    glm::vec2 min;
    glm::vec2 max;
} Bounds;

typedef struct entity 
{
    EntityID id;
    int flags; 
    Transform transform;
    RigidBody body;
    Bounds bounds;
    glm::vec3 color;
} Entity;

}