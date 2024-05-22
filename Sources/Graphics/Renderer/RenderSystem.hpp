#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Graphics/Buffers/Buffer.hpp"
#include "Core.hpp"

namespace Super 
{

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