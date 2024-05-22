#pragma once
#include "Core.hpp"
#include "RenderSystem.hpp"

namespace Super 
{
class Sprite2DSystem : public RenderSystem 
{
public:
    Sprite2DSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height);
    ~Sprite2DSystem();
    
    void Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) override;

    void UpdatePushConstants(Entity& ent);
};
}