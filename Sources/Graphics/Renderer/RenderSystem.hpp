#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Graphics/Buffers/Buffer.hpp"
#include "Graphics/Buffers/UniformBuffer.hpp"
#include "Core.hpp"
#include "SwapChain.hpp"
#include "Graphics/Descriptors/DescriptorHandler.hpp"
#include "Graphics/Descriptors/DescriptorWriter.hpp"

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

    virtual void Run(VkCommandBuffer commandBuffer, int frameIndex, std::vector<Entity>& entities) = 0;

protected:
    Device& mDevice;
  
    std::unique_ptr<Buffer> mVertexBuffer = nullptr;

    std::unique_ptr<std::unordered_map<std::string, Pipeline*>> mPipelines = nullptr;

    std::unique_ptr<DescriptorHandler> mDescriptorHandler = nullptr;

    std::unique_ptr<DescriptorWriter> mDescriptorWriter = nullptr;

};
}