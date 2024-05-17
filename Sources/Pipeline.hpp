#pragma once
#include <fstream>
#include <vector>
#include "Device.hpp"

namespace Super 
{

typedef struct pipeline_desc 
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
    // Vertices - not set by default.
    VkPipelineVertexInputStateCreateInfo vertexInfo;
} Pipeline_Desc;

class Pipeline 
{
public:
    Pipeline(std::shared_ptr<Device> device, Pipeline_Desc desc, const char* vertSrc, const char* fragSrc);
    ~Pipeline();

    // This class should not be copied or moved.
    Pipeline(const Pipeline& other) = delete;
    Pipeline operator=(const Pipeline& other) = delete;

    void Bind(VkCommandBuffer commandBuffer);

    static Pipeline_Desc DefaultPipelineDesc(uint32_t width, uint32_t height);
    
    void CreateGraphicsPipeline(Pipeline_Desc& desc, const char* vertSrc, const char* fragSrc);

private:
    // Reads the shader code from a file and returns the code as a vector of characters.
    const std::vector<char> ReadFromFile(const char* filePath) const;

    void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    std::shared_ptr<Device> mDevice = nullptr;
    VkPipeline mPipeline;
    VkShaderModule mVertexModule;
    VkShaderModule mFragmentModule;
};
}