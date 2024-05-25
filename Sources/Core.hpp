#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <list>

namespace Super 
{

//----------------------------------------------------------------
// Entity information.
//----------------------------------------------------------------
using EntityID = uint16_t;

typedef enum entityflags 
{
    ACTIVE              = 1,
    PLAYER_CONTROLLED   = 1 << 1,
    IS_RIGID            = 1 << 2,
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

typedef struct entity 
{
    EntityID id;
    int flags; 

    Transform tx;
    RigidBody body;

    glm::vec3 color;
    std::string label;
} Entity;

//----------------------------------------------------------------
// Collision objects.
//----------------------------------------------------------------

typedef struct cell 
{
    glm::vec2 position; // bottom left point for the cell.
    glm::vec2 size;
} Cell;

typedef struct collisionpair 
{
    Entity* A = nullptr;
    Entity* B = nullptr;
    
    collisionpair(Entity* a, Entity* b) {
        // Ensure entity1 is always less than entity2
        if (a < b) {
            A = a;
            B = b;
        } else {
            A = b;
            B = a;
        }
    }
    // Comparison operator that compares the labels of each entity.
    // Used for removing duplicates from the map of collision pairs, since we don't
    // want to register collisions more than once for any entitiy in a single frame.
    bool operator<(const collisionpair& other) const 
    {
        return (A->label < other.A->label) ||
            (A->label == other.A->label && B->label < other.B->label) ||
            (A->label == other.B->label && B->label < other.A->label);
    }

} CollisionPair;


typedef struct manifold 
{
    CollisionPair pair;
    float penetration{0.0f};
    glm::vec2 normal{0.0f};
} Manifold;


//----------------------------------------------------------------
// Objects to help organize important information for rendering.
//----------------------------------------------------------------

typedef struct simplepushconstants {
    alignas(16) glm::mat4 modelMatrix;
    alignas(16) glm::vec3 color{0.4f, 0.1f, 1.0f};
    alignas(16) glm::mat4 projectionViewMatrix{1.0f};
} SimplePushConstants;

typedef struct simpleuniformbuffer 
{
    glm::vec3 color{1.0f, 0.5f, 0.1f};
} SimpleUniformBuffer;

typedef struct pipelinedesc 
{
    // A static member funciton of Pipeline configures these to their default values.
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    // No default for these, since there's no such common configuration unlike the others.
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
    // Vertices - not set by default.
    VkPipelineVertexInputStateCreateInfo vertexInfo;
} PipelineDesc;

typedef struct swapchainsupportdetails 
{
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
} SwapChainSupportDetails;

typedef struct queuefamilyindices 
{
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;
  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
} QueueFamilyIndices;

typedef struct vertexbufferdec 
{
    VkVertexInputBindingDescription bindingDesc;
    std::vector<VkVertexInputAttributeDescription> attribsDesc;
} VertexBufferDesc;


}