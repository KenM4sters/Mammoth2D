#include "Graphics.hpp"

namespace mt 
{

Graphics::Graphics(Window& window)
    : mWindow{window}
{
    mSwapChain = std::make_unique<SwapChain>(mDevice, mWindow.GetExtent());
 
    RecreateSwapChain();
    CreateCommandBufffers();
}

Graphics::~Graphics() 
{
    FreeCommandBuffers();
}

VkCommandBuffer Graphics::GetCurrentCommandBuffer() const 
{
    assert(mIsFrameStarted && "Cannot get command buffer when frame is not in progress!");
    return mCommandBuffers[mCurrentFrameIndex];
}

inline const int& Graphics::GetFrameIndex() const 
{
    assert(mIsFrameStarted && "Cannot request frame index from renderer when the frame hasn't started!");
    return mCurrentFrameIndex;
}

VkCommandBuffer Graphics::Begin() 
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


void Graphics::End() 
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


void Graphics::RecreateSwapChain() 
{
    auto extent = mWindow.GetExtent();
    while(extent.width == 0 || extent.height == 0) 
    {
        extent = mWindow.GetExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(mDevice->GetDevice());

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

void Graphics::CreateCommandBufffers() 
{
    mCommandBuffers.resize(SwapChain::FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice->GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

    if(vkAllocateCommandBuffers(mDevice->GetDevice(), &allocInfo, mCommandBuffers.data()) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create command buffers!");
    }
}

void Graphics::PrepareGraphics(std::unique_ptr<IGame>& game) 
{
    
}

void Graphics::Update() 
{
    if(auto commandBuffer = Begin()) 
    {
        mRenderer->BeginRenderPass(commandBuffer, mSwapChain, mIsFrameStarted, mCurrentImageIndex);

        

        mRenderer->EndRenderPass(commandBuffer);
        End();
    }
}

void Graphics::FreeCommandBuffers() 
{
    vkFreeCommandBuffers(mDevice->GetDevice(), mDevice->GetCommandPool(), 
        static_cast<uint32_t>(mCommandBuffers.size()), mCommandBuffers.data());

    mCommandBuffers.clear();
}
}