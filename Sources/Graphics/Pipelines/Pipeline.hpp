#ifndef MAMMOTH_2D_PIPELINE_HPP
#define MAMMOTH_2D_PIPELINE_HPP

#include "Device.hpp"
#include "VertexInput.hpp"
#include "Shader.hpp"
#include "Graphics/Renderer/SwapChain.hpp"

#include <fstream>
#include <vector>

namespace mt 
{

struct PipelineDesc 
{
    // A static member funciton of Pipeline configures these to their default values.
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    // No default for these, since there's no such common configuration unlike the others.
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
    VkPipelineVertexInputStateCreateInfo vertexInfo;
};



class Pipeline 
{
public:
    Pipeline(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::unique_ptr<Shader> shader, VkPipelineBindPoint bindPoint);
    ~Pipeline();

    Pipeline(const Pipeline& other) = delete;
    Pipeline& operator=(const Pipeline& other) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    
    // Getters.
    //
    inline const VkPipelineLayout GetPipelineLayout() const { return mPipelineLayout; }
    inline const VkDescriptorSetLayout& GetDescriptorSetLayout() const { return mDescriptorSetLayout; }
    inline const VkPipelineBindPoint GetPipelineBindPoint() const { return mPipelineBindPoint; }
    inline const VkDescriptorPool GetDecsriptorPool() const { return mDescriptorPool; }
    inline const uint32_t& GetMaxDescriptorSets() const { return mMaxSets; }
    inline const std::unique_ptr<Shader>& GetShader() const { return mShader; }


private:
    PipelineDesc SetDefaultPipelineDesc(uint32_t width, uint32_t height);

    void CreateDescriptorPool();
    void CreateDescriptorLayout();
    void CreatePipelineLayout();
    void CreateGraphicsPipeline(VkRenderPass renderPass, uint32_t width, uint32_t height);

    Device& mDevice;

    std::unique_ptr<Shader> mShader = nullptr;

    VkPipeline mPipeline = VK_NULL_HANDLE;
    VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;
    VkPipelineBindPoint mPipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    
    VkDescriptorSetLayout mDescriptorSetLayout = VK_NULL_HANDLE;
};
}

#endif