#include <cassert>
#include <iostream>

#include "Pipeline.hpp"

namespace Super 
{
Pipeline::Pipeline(std::shared_ptr<Device> device, Pipeline_Desc desc, const char* vertSrc, const char* fragSrc)
    : mDevice{device}
{
    CreateGraphicsPipeline(desc, vertSrc, fragSrc);
}

Pipeline::~Pipeline() 
{
    vkDestroyShaderModule(mDevice->GetDevice(), mVertexModule, nullptr);
    vkDestroyShaderModule(mDevice->GetDevice(), mFragmentModule, nullptr);
    vkDestroyPipeline(mDevice->GetDevice(), mPipeline, nullptr);
}

const std::vector<char> Pipeline::ReadFromFile(const char* filePath) const 
{
    std::ifstream file{filePath, std::ios::ate | std::ios::binary};

    assert(file.is_open() && "File could not be opened!"); // check for errors - if thrown, double check file path.

    size_t fileSize = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void Pipeline::CreateGraphicsPipeline(Pipeline_Desc& desc, const char* vertSrc, const char* fragSrc) 
{
    // Before we begin to create the pipeline, make sure that a layout and render pass was properly
    // defined in the pipeline descriptor, since by default they're set to nullptrs.
    //
    assert(desc.pipelineLayout != VK_NULL_HANDLE 
        && "Attempting to create a pipeline from a Pipeline_Desc with a layout set to VK_NULL_HANDLE!"); 

    assert(desc.renderPass != VK_NULL_HANDLE 
        && "Attempting to create a pipeline from a Pipeline_Desc with a renderPass set to VK_NULL_HANDLE!"); 


    auto vertCode = ReadFromFile(vertSrc);
    auto fragCode = ReadFromFile(fragSrc);

    CreateShaderModule(vertCode, &mVertexModule);
    CreateShaderModule(fragCode, &mFragmentModule);

    VkPipelineShaderStageCreateInfo shaderStages[2];

    // Vertex shader.
    //
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = mVertexModule;
    shaderStages[0].pName = "main";
    shaderStages[0].flags = 0;
    shaderStages[0].pSpecializationInfo = nullptr;
    shaderStages[0].pNext = nullptr;
    // Fragment shader.
    //
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = mFragmentModule;
    shaderStages[1].pName = "main";
    shaderStages[1].flags = 0;
    shaderStages[1].pSpecializationInfo = nullptr;
    shaderStages[1].pNext = nullptr;



    VkPipelineViewportStateCreateInfo viewportInfo{};
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = &desc.viewport;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = &desc.scissor;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &desc.vertexInfo;
    pipelineInfo.pInputAssemblyState = &desc.inputAssemblyInfo;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &desc.rasterizationInfo;
    pipelineInfo.pMultisampleState = &desc.multisampleInfo;
    pipelineInfo.pColorBlendState = &desc.colorBlendInfo;
    pipelineInfo.pDepthStencilState = &desc.depthStencilInfo;
    pipelineInfo.pDynamicState = nullptr;

    pipelineInfo.layout = desc.pipelineLayout;
    pipelineInfo.renderPass = desc.renderPass;
    pipelineInfo.subpass = desc.subpass;

    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if(vkCreateGraphicsPipelines(mDevice->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &mPipeline) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }

}

void Pipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) 
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.codeSize = code.size();
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if(vkCreateShaderModule(mDevice->GetDevice(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create shader module!");
    }

}

Pipeline_Desc Pipeline::DefaultPipelineDesc(uint32_t width, uint32_t height) 
{
    Pipeline_Desc desc{};

    desc.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    desc.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    desc.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

    desc.viewport.x = 0.0f;
    desc.viewport.y = 0.0f;
    desc.viewport.width = static_cast<float>(width);
    desc.viewport.height = static_cast<float>(height);
    desc.viewport.minDepth = 0.0f;
    desc.viewport.maxDepth = 1.0f;

    desc.scissor.offset = {0, 0};
    desc.scissor.extent = {width, height};


    desc.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    desc.rasterizationInfo.depthClampEnable = VK_FALSE;
    desc.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
    desc.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
    desc.rasterizationInfo.lineWidth = 1.0f;
    desc.rasterizationInfo.cullMode = VK_CULL_MODE_NONE;
    desc.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    desc.rasterizationInfo.depthBiasEnable = VK_FALSE;
    desc.rasterizationInfo.depthBiasConstantFactor = 0.0f;
    desc.rasterizationInfo.depthBiasClamp = 0.0f;
    desc.rasterizationInfo.depthBiasSlopeFactor = 0.0f;


    desc.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    desc.multisampleInfo.sampleShadingEnable = VK_FALSE;
    desc.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    desc.multisampleInfo.minSampleShading = 1.0f;
    desc.multisampleInfo.pSampleMask = nullptr;
    desc.multisampleInfo.alphaToCoverageEnable = VK_FALSE;
    desc.multisampleInfo.alphaToOneEnable = VK_FALSE;


    desc.colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT 
                                            | VK_COLOR_COMPONENT_G_BIT 
                                            | VK_COLOR_COMPONENT_B_BIT 
                                            | VK_COLOR_COMPONENT_A_BIT;
    desc.colorBlendAttachment.blendEnable = VK_FALSE;
    desc.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    desc.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    desc.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    desc.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    desc.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    desc.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    desc.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    desc.colorBlendInfo.logicOpEnable = VK_FALSE;
    desc.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
    desc.colorBlendInfo.attachmentCount = 1;
    desc.colorBlendInfo.pAttachments = &desc.colorBlendAttachment;
    desc.colorBlendInfo.blendConstants[0] = 0.0f;
    desc.colorBlendInfo.blendConstants[1] = 0.0f;
    desc.colorBlendInfo.blendConstants[2] = 0.0f;
    desc.colorBlendInfo.blendConstants[3] = 0.0f;


    desc.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    desc.depthStencilInfo.depthTestEnable = VK_TRUE;
    desc.depthStencilInfo.depthWriteEnable = VK_TRUE;
    desc.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    desc.depthStencilInfo.stencilTestEnable = VK_TRUE;
    desc.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
    desc.depthStencilInfo.minDepthBounds = 0.0f;
    desc.depthStencilInfo.maxDepthBounds = 1.0f;
    desc.depthStencilInfo.front = {};
    desc.depthStencilInfo.back = {};

    return desc;
}

void Pipeline::Bind(VkCommandBuffer commandBuffer) 
{
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mPipeline);
}

}