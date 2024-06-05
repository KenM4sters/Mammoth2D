#include "Renderer.hpp"
#include "Sprite2DSystem.hpp"
#include <cassert>

namespace mt 
{
Renderer::Renderer(Device& device, Window& window) 
    : mDevice{device}, mWindow{window}
{
    mSwapChain = std::make_unique<SwapChain>(mDevice, mWindow.GetExtent());

    RenderSystem* spriteSystem = new Sprite2DSystem(mDevice, mSwapChain->GetRenderPass(), mSwapChain->GetWidth(), mSwapChain->GetHeight());
    mRenderSystems.push_back(spriteSystem);   

    RecreateSwapChain();
    CreateCommandBufffers();
    
}

Renderer::~Renderer() 
{
    FreeCommandBuffers();
    for(const auto& system : mRenderSystems) 
    {
        delete system;
    }
}


void Renderer::RecreateSwapChain() 
{
    auto extent = mWindow.GetExtent();
    while(extent.width == 0 || extent.height == 0) 
    {
        extent = mWindow.GetExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(mDevice.GetDevice());

    if(mSwapChain == nullptr) 
    {
        mSwapChain = std::make_unique<SwapChain>(mDevice, extent);   
    } 
    else {
        std::shared_ptr<SwapChain> oldSwapChain = std::move(mSwapChain);
        mSwapChain = std::make_unique<SwapChain>(mDevice, extent, oldSwapChain);

        if(!oldSwapChain->compareSwapFormats(*mSwapChain.get())) 
        {
            throw std::runtime_error("Swap chain image(or depth) format has changed!");
        }
    }
}

VkCommandBuffer Renderer::GetCurrentCommandBuffer() const 
{
    assert(mIsFrameStarted && "Cannot get command buffer when frame is not in progress!");
    return mCommandBuffers[mCurrentFrameIndex];
}

void Renderer::CreateCommandBufffers() 
{
    mCommandBuffers.resize(SwapChain::FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice.GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

    if(vkAllocateCommandBuffers(mDevice.GetDevice(), &allocInfo, mCommandBuffers.data()) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create command buffers!");
    }
}

VkCommandBuffer Renderer::Begin() 
{
    assert(!mIsFrameStarted && "Can't call begin frame while already in progress");

    auto result = mSwapChain->AcquireNextImage(&mCurrentImageIndex);

    if(result == VK_ERROR_OUT_OF_DATE_KHR) 
    {
        RecreateSwapChain();
        return nullptr;
    }

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
    {
        throw std::runtime_error("Fail to acquire next swapchain image");
    }

    mIsFrameStarted = true;
    auto commandBuffer = GetCurrentCommandBuffer();

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }

    return commandBuffer;
}

void Renderer::Render(VkCommandBuffer commandBuffer) 
{
    for(auto& system : mRenderSystems) 
    {
        system->Run(commandBuffer, mCurrentFrameIndex);
    }
}

void Renderer::FreeCommandBuffers() 
{
    vkFreeCommandBuffers(mDevice.GetDevice(), mDevice.GetCommandPool(), 
        static_cast<uint32_t>(mCommandBuffers.size()), mCommandBuffers.data());

    mCommandBuffers.clear();
}

void Renderer::BeginRenderPass(VkCommandBuffer commandBuffer) 
{
    assert(mIsFrameStarted && "Can't call beginSwapchainProgess() if frame is not in progress!");
    assert(commandBuffer == GetCurrentCommandBuffer() &&
            "Can't begin render pass on a command buffer that's from a different frame!");

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = mSwapChain->GetRenderPass();
    renderPassInfo.framebuffer = mSwapChain->GetFrameBuffer(mCurrentImageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = mSwapChain->GetSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.01, 0.01f, 0.01f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(mSwapChain->GetSwapChainExtent().width);
    viewport.height = static_cast<float>(mSwapChain->GetSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0,0}, mSwapChain->GetSwapChainExtent()};
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void Renderer::EndRenderPass(VkCommandBuffer commandBuffer) 
{
    assert(mIsFrameStarted && "Can't call endSwapchainProgess() if frame is not in progress!");
    assert(commandBuffer == GetCurrentCommandBuffer() &&
            "Can't end render pass on a command buffer that's from a different frame!");

    vkCmdEndRenderPass(commandBuffer);
}


void Renderer::End() 
{
    assert(mIsFrameStarted && "Can't call end frame while frame is not in progress!");
    auto commandBuffer = GetCurrentCommandBuffer();
    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to record command buffers!");
    }

    auto result = mSwapChain->SubmitCommandBuffers(&commandBuffer, &mCurrentImageIndex);

    // Window Resize handling - TODO
    //

    mIsFrameStarted = false;
    mCurrentFrameIndex = (mCurrentFrameIndex + 1) % SwapChain::FRAMES_IN_FLIGHT;
}

}