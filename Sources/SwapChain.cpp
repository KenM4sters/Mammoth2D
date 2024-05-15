#include "SwapChain.hpp"


namespace Super 
{
SwapChain::SwapChain(std::shared_ptr<Device>& device, VkExtent2D extent)
    : mDevice{device}, mWindowExtent{extent}
{
    Init();
}   

SwapChain::SwapChain(std::shared_ptr<Device>& device, VkExtent2D extent, std::shared_ptr<SwapChain>& previous)
    : mDevice{device}, mWindowExtent{extent}, mPreviousSwapChain{previous}
{
    Init();
    mPreviousSwapChain = nullptr;
}

SwapChain::~SwapChain() 
{
    for (auto imageView : mSwapChainImageViews) 
    {
        vkDestroyImageView(mDevice->GetDevice(), imageView, nullptr);
    }
    mSwapChainImageViews.clear();

    if (mSwapChain != nullptr) 
    {
        vkDestroySwapchainKHR(mDevice->GetDevice(), mSwapChain, nullptr);
        mSwapChain = nullptr;
    }

    for (int i = 0; i < mDepthImages.size(); i++) 
    {
        vkDestroyImageView(mDevice->GetDevice(), mDepthImageViews[i], nullptr);
        vkDestroyImage(mDevice->GetDevice(), mDepthImages[i], nullptr);
        vkFreeMemory(mDevice->GetDevice(), mDepthImageMemorys[i], nullptr);
    }

    for (auto framebuffer : mSwapChainFramebuffers) 
    {
        vkDestroyFramebuffer(mDevice->GetDevice(), framebuffer, nullptr);
    }

    vkDestroyRenderPass(mDevice->GetDevice(), mRenderPass, nullptr);

    // cleanup synchronization objects
    for (size_t i = 0; i < FRAMES_IN_FLIGHT; i++) 
    {
        vkDestroySemaphore(mDevice->GetDevice(), mRenderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(mDevice->GetDevice(), mImageAvailableSemaphores[i], nullptr);
        vkDestroyFence(mDevice->GetDevice(), mInFlightFences[i], nullptr);
    }
}

void SwapChain::Init() 
{
    CreateSwapChain();
    CreateImageViews();
    CreateRenderPass();
    CreateDepthResources();
    CreateFramebuffers();
    CreateSyncObjects();
}

void SwapChain::CreateSwapChain() 
{
    Swap_Chain_Support_Details swapChainSupport = mDevice->GetSwapChainSupport();

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupport.capabilities.maxImageCount) 
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = mDevice->GetSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    Queue_Family_Indices indices = mDevice->FindPhysicalQueueFamilies();
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

    if (indices.graphicsFamily != indices.presentFamily) 
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;      // Optional
        createInfo.pQueueFamilyIndices = nullptr;  // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = mPreviousSwapChain == nullptr ? VK_NULL_HANDLE : mPreviousSwapChain->mSwapChain;

    if (vkCreateSwapchainKHR(mDevice->GetDevice(), &createInfo, nullptr, &mSwapChain) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    // we only specified a minimum number of images in the swap chain, so the implementation is
    // allowed to create a swap chain with more. That's why we'll first query the final number of
    // images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
    // retrieve the handles.
    vkGetSwapchainImagesKHR(mDevice->GetDevice(), mSwapChain, &imageCount, nullptr);
    mSwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(mDevice->GetDevice(), mSwapChain, &imageCount, mSwapChainImages.data());

    mSwapChainImageFormat = surfaceFormat.format;
    mSwapChainExtent = extent;
}

void SwapChain::CreateImageViews() 
{

}

void SwapChain::CreateDepthResources() 
{

}

void SwapChain::CreateRenderPass() 
{

}

void SwapChain::CreateFramebuffers() 
{

}

void SwapChain::CreateSyncObjects() 
{

}

VkFormat SwapChain::FindDepthFormat() 
{

}

VkResult SwapChain::AcquireNextImage(uint32_t *imageIndex) 
{

}

VkResult SwapChain::SubmitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex) 
{

}


// Helper Functions.
//----------------------------------------------------------------
VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) 
{

}

VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) 
{

}

VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) 
{

}

//----------------------------------------------------------------



}