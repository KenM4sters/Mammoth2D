#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include "../Pipeline.hpp"
#include "Entity.hpp"

namespace Super 
{
typedef struct SimplePushConstants {
    Transform transform{};
    alignas(16) glm::vec3 color{0.4f, 0.1f, 1.0f};
    alignas(16) glm::mat4 projectionViewMatrix{1.0f};

} SimplePushConstants;

class RenderSystem 
{
public: 
    RenderSystem(const std::shared_ptr<Device>& device, VkRenderPass renderPass, uint32_t width, uint32_t height)
        : mDevice{device} 
    {
    }

    virtual ~RenderSystem() 
    {
        vkDestroyPipelineLayout(mDevice->GetDevice(), mPipelineLayout, nullptr);
    }

    virtual void CreatePipelineLayout() = 0;

    virtual void CreatePipeline(uint32_t width, uint32_t height, VkRenderPass renderPass) = 0;

    virtual void UpdateBuffers() = 0;

    virtual void Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) = 0;

protected:

    std::shared_ptr<Device> mDevice = nullptr;
    std::unique_ptr<Pipeline> mPipeline = nullptr;
    VkPipelineLayout mPipelineLayout{};
};
}