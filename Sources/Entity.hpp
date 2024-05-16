#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <vector>

namespace Super 
{
using EntityID = uint16_t;

typedef enum entity_flags 
{
    ACTIVE              = 1,
    PLAYER_CONTROLLED   = 1 << 1,
    IS_RIGID            = 1 << 2,
    HAS_MOTION          = 1 << 3,
    HAS_HEALTH          = 1 << 4,    
} Entity_Flags;

typedef struct vertex 
{
    glm::vec2 position;
    glm::vec3 color;
} Vertex;

typedef struct renderable 
{
    VkBuffer vertexBuffer;
    std::vector<Vertex> vertices;
} Renderable;

typedef struct bounds 
{
    glm::vec2 position;
    glm::vec2 size;
} Bounds;

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
    glm::vec2 position;
    glm::vec2 size;
    Physics physics;
    Renderable renderable;
} Entity;
}