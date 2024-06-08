#include "Renderer.hpp"
#include <cassert>

namespace mt 
{
Renderer::Renderer(LogicalDevice& logicalDevice, Window& window) 
    : mLogicalDevice{logicalDevice}, mWindow{window}
{

}

Renderer::~Renderer() 
{

}

void Renderer::CreateDescriptorPool(uint32_t uniformCount, uint32_t imageCount) 
{
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[0].descriptorCount = imageCount;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[1].descriptorCount = uniformCount;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = (uniformCount + imageCount) * 2;

    if(vkCreateDescriptorPool(mLogicalDevice.GetDevice(), &poolInfo, nullptr, &mDescriptorPool) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create descriptor pool");
    }
}

void Renderer::CreateDescriptorSet(VkDescriptorSet* descriptorSet, VkDescriptorType type, VkShaderStageFlags flags) 
{
    VkDescriptorSetLayout layout = nullptr;

    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = type;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = flags;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if(vkCreateDescriptorSetLayout(mLogicalDevice.GetDevice(), &layoutInfo, nullptr, &layout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create descriptor set layout!");
    }

    mDescriptorSetLayouts.push_back(layout);

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = mDescriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &layout;

    if(vkAllocateDescriptorSets(mLogicalDevice.GetDevice(), &allocInfo, descriptorSet) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }
}


void Renderer::Render(VkCommandBuffer commandBuffer) 
{

}

void Renderer::BeginRenderPass(VkCommandBuffer commandBuffer, std::unique_ptr<SwapChain>& swapChain, bool started, uint32_t currentImageIndex) 
{
    assert(started && "Can't call beginSwapchainProgess() if frame is not in progress!");

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = swapChain->GetRenderPass();
    renderPassInfo.framebuffer = swapChain->GetFrameBuffer(currentImageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChain->GetSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.01, 0.01f, 0.01f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapChain->GetSwapChainExtent().width);
    viewport.height = static_cast<float>(swapChain->GetSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0,0}, swapChain->GetSwapChainExtent()};
    
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void Renderer::EndRenderPass(VkCommandBuffer commandBuffer) 
{
    vkCmdEndRenderPass(commandBuffer);
}


}