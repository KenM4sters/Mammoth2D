#ifndef MAMMOTH_2D_RENDERER_HPP
#define MAMMOTH_2D_RENDERER_HPP

#include "SwapChain.hpp"
#include "Game.hpp"

#include <glm/glm.hpp>

#include <iostream>

namespace mt 
{
class Renderer 
{
public:
    Renderer(LogicalDevice& logicalDevice, Window& window);
    ~Renderer();

    void BeginRenderPass(VkCommandBuffer commandBuffer, std::unique_ptr<SwapChain>& swapChain, bool started, uint32_t currentImageIndex);
    
    void Render(VkCommandBuffer commandBuffer);
    
    void EndRenderPass(VkCommandBuffer commandBuffer);

    void CreateDescriptorPool(uint32_t uniformCount, uint32_t imageCount);

    void CreateDescriptorSet(VkDescriptorSet* descriptorSet, VkDescriptorType type, VkShaderStageFlags flags);

private:
    LogicalDevice& mLogicalDevice;
    Window& mWindow;

    VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;
    uint32_t mMaxSets = SwapChain::FRAMES_IN_FLIGHT;

    std::vector<VkDescriptorSetLayout> mDescriptorSetLayouts{};
};
}


#endif