#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include "../Pipeline.hpp"
#include "Entity.hpp"

namespace Super 
{
typedef struct SimplePushConstants {
    Transform transform;
    glm::vec3 color{1.0f, 0.0f, 1.0f};
    glm::mat3 projectionViewMatrix{1.0f};

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

    virtual void Run(VkCommandBuffer commandBuffer) = 0;

protected:
    std::shared_ptr<Device> mDevice = nullptr;
    std::unique_ptr<Pipeline> mPipeline = nullptr;
    VkPipelineLayout mPipelineLayout{};
};
}