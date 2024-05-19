#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Scene/Entity.hpp"
#include "Graphics/Buffers/Buffer.hpp"

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
    RenderSystem(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height)
        : mDevice{device} 
    {
    }

    virtual ~RenderSystem() 
    {
        for(const auto& pipeline : *mPipelines.get()) 
        {
            delete pipeline.second;
        }
    }

    virtual void Run(VkCommandBuffer commandBuffer, std::vector<Entity>& entities) = 0;

protected:
    Device& mDevice;

    SimplePushConstants mPushConstants{};

    std::unique_ptr<Buffer> mVertexBuffer = nullptr;

    std::unique_ptr<std::unordered_map<std::string, Pipeline*>> mPipelines = nullptr;

};
}