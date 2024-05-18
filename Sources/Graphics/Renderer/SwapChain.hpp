#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"

namespace Super 
{
class SwapChain 
{
public:
    SwapChain(Device& device, VkExtent2D extent);
    SwapChain(Device& device, VkExtent2D extent, std::shared_ptr<SwapChain>& previous);
    ~SwapChain();

    SwapChain(const SwapChain& other) = delete;
    SwapChain& operator=(const SwapChain& other) = delete;

    static constexpr int FRAMES_IN_FLIGHT = 2;


    // Getters
    //
    inline VkFramebuffer GetFrameBuffer(int index) const { return mSwapChainFramebuffers[index]; }
    inline VkRenderPass GetRenderPass() const { return mRenderPass; }
    inline VkImageView GetImageView(int index) const { return mSwapChainImageViews[index]; }
    inline size_t GetImageCount() const { return mSwapChainImages.size(); }
    inline VkFormat GetSwapChainImageFormat() const { return mSwapChainImageFormat; }
    inline VkExtent2D GetSwapChainExtent() const { return mSwapChainExtent; }
    inline uint32_t GetWidth() const { return mSwapChainExtent.width; }
    inline uint32_t GetHeight() const { return mSwapChainExtent.height; }

    float GetExtentAspectRatio() 
    {
        return static_cast<float>(mSwapChainExtent.width) / (mSwapChainExtent.height);
    }

    VkFormat FindDepthFormat();
    VkResult AcquireNextImage(uint32_t *imageIndex);
    VkResult SubmitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

    bool compareSwapFormats(const SwapChain& swapChain) const 
    {
        return swapChain.mSwapChainDepthFormat == mSwapChainDepthFormat &&
            swapChain.mSwapChainImageFormat == mSwapChainImageFormat;
    }

private:
    void Init();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateDepthResources();
    void CreateRenderPass();
    void CreateFramebuffers();
    void CreateSyncObjects();

    // Helper functions
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    Device& mDevice;
    std::shared_ptr<SwapChain> mPreviousSwapChain = nullptr;
    VkExtent2D mWindowExtent;
    VkSwapchainKHR mSwapChain;

    VkFormat mSwapChainImageFormat;
    VkFormat mSwapChainDepthFormat;
    VkExtent2D mSwapChainExtent;
    VkRenderPass mRenderPass;

    std::vector<VkFramebuffer> mSwapChainFramebuffers;
    std::vector<VkImage> mDepthImages;
    std::vector<VkDeviceMemory> mDepthImageMemorys;
    std::vector<VkImageView> mDepthImageViews;
    std::vector<VkImage> mSwapChainImages;
    std::vector<VkImageView> mSwapChainImageViews;
    std::vector<VkSemaphore> mImageAvailableSemaphores;
    std::vector<VkSemaphore> mRenderFinishedSemaphores;
    std::vector<VkFence> mInFlightFences;
    std::vector<VkFence> mImagesInFlight;

    size_t mCurrentFrame = 0;

};
}