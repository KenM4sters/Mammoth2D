#include <cassert>
#include <iostream>
#include "Pipeline.hpp"
#include "Graphics/Renderer/RenderSystem.hpp"

namespace Super 
{

Pipeline::Pipeline(Device& device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::unique_ptr<Shader> shader, VkPipelineBindPoint bindPoint)
    : mDevice{device}
{
    mShader = std::move(shader);
    
    CreateDescriptorPool();
    CreateDescriptorLayout();
    CreatePipelineLayout();
    CreateGraphicsPipeline(renderPass, width, height);
}

Pipeline::~Pipeline() 
{
    vkDestroyDescriptorPool(mDevice.GetDevice(), mDescriptorPool, nullptr);
    vkDestroyPipelineLayout(mDevice.GetDevice(), mPipelineLayout, nullptr);
    vkDestroyPipeline(mDevice.GetDevice(), mPipeline, nullptr);
}

void Pipeline::CreateDescriptorPool() 
{
    mPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    mPoolSize.descriptorCount = mMaxSets;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &mPoolSize;
    poolInfo.maxSets = mMaxSets;

    if(vkCreateDescriptorPool(mDevice.GetDevice(), &poolInfo, nullptr, &mDescriptorPool) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create descriptor pool");
    }
}


void Pipeline::CreateDescriptorLayout() 
{
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = mShader->GetUniform().GetFlags();
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if(vkCreateDescriptorSetLayout(mDevice.GetDevice(), &layoutInfo, nullptr, &mDescriptorSetLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create descriptor set layout!");
    }
}

void Pipeline::CreatePipelineLayout() 
{
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstants);
 
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &mDescriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
    
    if(vkCreatePipelineLayout(mDevice.GetDevice(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void Pipeline::CreateGraphicsPipeline(VkRenderPass renderPass, uint32_t width, uint32_t height) 
{

    PipelineDesc desc = SetDefaultPipelineDesc(width, height);

    // Vertex Info.
    //
    const auto& vertexInput = mShader->GetVertexInput();
    desc.vertexInfo.vertexAttributeDescriptionCount = vertexInput.GetAttribDescriptions().size();
    desc.vertexInfo.vertexBindingDescriptionCount = 1;
    desc.vertexInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    desc.vertexInfo.pVertexBindingDescriptions = &vertexInput.GetBindingDescriptions()[0];
    desc.vertexInfo.pVertexAttributeDescriptions = vertexInput.GetAttribDescriptions().data();

    desc.renderPass = renderPass;
    desc.pipelineLayout = mPipelineLayout;

    // Before we begin to create the pipeline, make sure that a layout and render pass was properly
    // defined in the pipeline descriptor, since by default they're set to nullptrs.
    //
    assert(desc.pipelineLayout != VK_NULL_HANDLE 
        && "Attempting to create a pipeline from a Pipeline_Desc with a layout set to VK_NULL_HANDLE!"); 

    assert(desc.renderPass != VK_NULL_HANDLE 
        && "Attempting to create a pipeline from a Pipeline_Desc with a renderPass set to VK_NULL_HANDLE!"); 


    VkPipelineViewportStateCreateInfo viewportInfo{};
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = &desc.viewport;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = &desc.scissor;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = mShader->GetShaderStages().data();
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

    if(vkCreateGraphicsPipelines(mDevice.GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &mPipeline) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }

}


PipelineDesc Pipeline::SetDefaultPipelineDesc(uint32_t width, uint32_t height) 
{
    PipelineDesc desc{};

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