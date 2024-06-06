#include "Renderer.hpp"
#include <cassert>

namespace mt 
{
Renderer::Renderer(Device& device, Window& window) 
    : mDevice{device}, mWindow{window}
{

}

Renderer::~Renderer() 
{

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



void Renderer::DrawQuad(glm::vec2 size, glm::vec2 position, glm::vec3 color) 
{
    
}

void Renderer::DrawTempObj(TempRenderObj& obj) 
{
    
}


}