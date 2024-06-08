#include "Graphics.hpp"

namespace mt 
{

Graphics::Graphics(Window& window)
    : mWindow{window},
    mInstance{std::make_unique<Instance>(mWindow)},
    mPhysicalDevice{std::make_unique<PhysicalDevice>(*mInstance)},
    mLogicalDevice{std::make_unique<LogicalDevice>(*mPhysicalDevice)},
    mSwapChain{std::make_unique<SwapChain>(*mPhysicalDevice, *mLogicalDevice, mWindow.GetExtent())},
    mCommandPool{std::make_unique<CommandPool>(*mPhysicalDevice, *mLogicalDevice)},
    mCommandBuffers{{std::make_unique<CommandBuffer>(*mLogicalDevice, *mCommandPool)}}
{
    RecreateSwapChain();
}

VkCommandBuffer Graphics::Begin() 
{
    assert(!mHasFrameStarted && "Can't call begin frame while already in progress");

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

    mHasFrameStarted = true;

    mCommandBuffers[mCurrentFrameIndex]->Begin();
}


void Graphics::End() 
{
    auto commandBuffer = mCommandBuffers[mCurrentFrameIndex]->End();

    auto result = mSwapChain->SubmitCommandBuffers(&commandBuffer, &mCurrentImageIndex);

    // Window Resize handling - TODO
    //
    mHasFrameStarted = false;
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

    vkDeviceWaitIdle(mLogicalDevice->GetDevice());

    if(mSwapChain == nullptr) 
    {
        mSwapChain = std::make_unique<SwapChain>(mPhysicalDevice, mLogicalDevice, extent);   
    } 
    else {
        std::shared_ptr<SwapChain> oldSwapChain = std::move(mSwapChain);
        mSwapChain = std::make_unique<SwapChain>(mPhysicalDevice, mLogicalDevice, extent, oldSwapChain);

        if(!oldSwapChain->compareSwapFormats(*mSwapChain.get())) 
        {
            throw std::runtime_error("Swap chain image(or depth) format has changed!");
        }
    }
}

void Graphics::PrepareGraphics(IGame& game) 
{

    uint32_t nCameraComps;
    uint32_t nTextureComps;
    uint32_t nTransformComps;

    for(const auto& renderable : game.GetObj()) 
    {
        // Create a shader Prefab here.
        if(renderable.camera) nCameraComps += 1;
        if(renderable.transform) nTransformComps += 1;
        if(renderable.material) nTextureComps += 1;
    }

    mRenderer->CreateDescriptorPool(nCameraComps + nTransformComps, nTextureComps);
    
    for(const auto& renderable : game.GetObj()) 
    {
        if(renderable.camera) 
        {
            mRenderer->CreateDescriptorSet(&renderable.camera->descriptorSet, 
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
        }
        
        if(renderable.transform) 
        {
            mRenderer->CreateDescriptorSet(&renderable.transform->descriptorSet, 
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
        }

        if(renderable.material) 
        {
            mRenderer->CreateDescriptorSet(&renderable.material->descriptorSet, 
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT);
        }
    } 


    // 1 descriptor set for camera
    // numOfTextures descripor sets for each texture
    // numOfRenderables descriptor sets for each renderable.
    // 1 pipeline layout per shader file.

}

void Graphics::Update() 
{
    if(auto commandBuffer = Begin()) 
    {
        mRenderer->BeginRenderPass(commandBuffer, mSwapChain, mHasFrameStarted, mCurrentImageIndex);

        

        mRenderer->EndRenderPass(commandBuffer);
        End();
    }
}
}