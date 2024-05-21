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
    PLAYER_CONTROLLED   = 1 << 1,
} EntityFlags;

typedef struct rigidbody 
{
    float inverseMass;
    float denisty;
    float restitution;
    glm::vec2 force;
    glm::vec2 velocity;
} RigidBody; 

typedef struct transform 
{
    glm::vec2 position;
    glm::vec2 scale;    
} Transform; 

typedef struct bounds 
{
    glm::vec2 min;
    glm::vec2 max;
} Bounds;

typedef struct entity 
{
    EntityID id;
    int flags; 
    Transform tx;
    RigidBody body;
    Bounds bounds;
    glm::vec3 color;
    std::string label;
} Entity;

}