#pragma once
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Graphics/Buffers/Buffer.hpp"
#include "Graphics/Buffers/UniformBuffer.hpp"
#include "SwapChain.hpp"
#include "Graphics/Descriptors/DescriptorHandler.hpp"
#include "Graphics/Descriptors/DescriptorWriter.hpp"

namespace mt 
{

struct TexturePushConstant {
    glm::mat4 modelMatrix{1.0f};
    alignas(16) glm::mat4 projectionViewMatrix{1.0f};
    alignas(4) int entId;
} ;

struct SimpleUniformBuffer 
{
    glm::vec3 color{1.0f, 0.5f, 0.1f};
};

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

    virtual void Run(VkCommandBuffer commandBuffer, int frameIndex) = 0;

protected:
    Device& mDevice;
  
    std::unique_ptr<Buffer> mVertexBuffer = nullptr;

    std::unique_ptr<std::unordered_map<std::string, Pipeline*>> mPipelines = nullptr;

    std::unique_ptr<DescriptorHandler> mDescriptorHandler = nullptr;

    std::unique_ptr<DescriptorWriter> mDescriptorWriter = nullptr;

};
}