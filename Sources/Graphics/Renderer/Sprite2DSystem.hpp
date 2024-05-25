#pragma once
#include "Core.hpp"
#include "RenderSystem.hpp"
#include "Graphics/Images/Image.hpp"

namespace Super 
{
class Sprite2DSystem : public RenderSystem 
{
public:
    Sprite2DSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height);
    ~Sprite2DSystem();
    
    void Run(VkCommandBuffer commandBuffer, int frameIndex, std::vector<Entity>& entities) override;

    void UpdatePushConstants(Entity& ent);

private:
    std::unique_ptr<Image> mImage = nullptr;

    glm::vec2 mTexCoords[6][6];
};
}