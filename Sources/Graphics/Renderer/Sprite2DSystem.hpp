#pragma once
#include "RenderSystem.hpp"
#include "Graphics/Images/Image.hpp"

namespace mt 
{
class Sprite2DSystem : public RenderSystem 
{
public:
    Sprite2DSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height);
    ~Sprite2DSystem();
    
    void Run(VkCommandBuffer commandBuffer, int frameIndex) override;

private:
    glm::vec2 mTexCoords[6][6];

    std::vector<std::unique_ptr<Image>> mImages{};
};
}