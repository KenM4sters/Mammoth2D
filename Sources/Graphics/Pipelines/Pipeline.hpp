#pragma once
#include <fstream>
#include <vector>
#include "Device.hpp"
#include "VertexInput.hpp"
#include "Shader.hpp"

namespace Super 
{


class Pipeline 
{
public:
    Pipeline(Device& device, VkRenderPass renderPass, VertexInput vertexInput, const char* vertSrc, const char* fragSrc, uint32_t width, uint32_t height);
    ~Pipeline();

    Pipeline(const Pipeline& other) = delete;
    Pipeline& operator=(const Pipeline& other) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    

    // Getters.
    //
    inline const VkPipelineLayout GetPipelineLayout() const { return mPipelineLayout; }

private:
    void CreatePipelineLayout();

    void CreateGraphicsPipeline(VertexInput input, VkRenderPass renderPass, uint32_t width, uint32_t height);

    PipelineDesc SetDefaultPipelineDesc(uint32_t width, uint32_t height);

    Device& mDevice;

    std::unique_ptr<Shader> mShader = nullptr;

    VkPipeline mPipeline = VK_NULL_HANDLE;
    VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;
};
}