#pragma once
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_beta.h>
#include "Core.hpp"
#include "Window.hpp"

namespace Super 
{

class Device 
{
public:
    Device(Window& window);
    ~Device();

    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    VkPhysicalDeviceProperties mPhysicalDeviceProps;

    // Getters.
    //
    inline const VkDevice GetDevice() const { return mDevice; }
    inline const VkSurfaceKHR GetSurface() const { return mSurface; }
    inline const VkCommandPool GetCommandPool() const { return mCommandPool; }
    inline const VkQueue GetGraphicsQueue() const { return mGraphicsQueue; }
    inline const VkQueue GetPresentQueue() const { return mPresentQueue; }
    inline const VkPhysicalDevice GetPhysicalDevice() const { return mPhysicalDevice; }
    
    // Even though we already run call these functions from within the implementation, we're choosing
    // not to store them within the class since they're not really required by all but a handful of
    // other classes, so we'll make getters for these private functions as well.
    //
    SwapChainSupportDetails GetSwapChainSupport() { return CheckSwapChainSupport(mPhysicalDevice); }
    QueueFamilyIndices FindPhysicalQueueFamilies() { return FindQueueFamilies(mPhysicalDevice); }

    // Helper functions for interacting with buffers from outside of this class
    // (typically from the pipeline class).
    //
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkFormat FindSupportedFormat(
        const std::vector<VkFormat> &candidates, 
        VkImageTiling tiling, 
        VkFormatFeatureFlags features
    );

    void CreateBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer &buffer,
        VkDeviceMemory &bufferMemory
    );

    void CopyBufferToImage(
        VkBuffer buffer, 
        VkImage image, 
        uint32_t width, 
        uint32_t height, 
        uint32_t layerCount
    );

    void CreateImageFromInfo(
        const VkImageCreateInfo &imageInfo,
        VkMemoryPropertyFlags properties,
        VkImage &image,
        VkDeviceMemory &imageMemory
    );

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    VkCommandBuffer BeginSingleTimeCommands();

    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);


private:

    void CreateInstance();
    void CreateSurface();
    void ChoosePhysicalDevice();
    void CreateLogicalDevice();
    void SetupDebugMessenger();
    void CreateCommandPool();


    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    bool CheckValidationLayerSupport() const;
    void HasGLFWRequiredExtensions() const;
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;
    SwapChainSupportDetails CheckSwapChainSupport(VkPhysicalDevice device) const;

    void ConfigureDebugMessengerCallback(VkDebugUtilsMessengerCreateInfoEXT& createInfo) const;
    
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;

    const std::vector<const char*> GetAllRequiredExtensions() const;
    
    Window& mWindow;

    VkInstance mInstance;
    VkDevice mDevice;
    VkSurfaceKHR mSurface;
    VkQueue mGraphicsQueue;
    VkQueue mPresentQueue;

    VkDebugUtilsMessengerEXT mDebugMessenger;
    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    VkCommandPool mCommandPool;


    const std::vector<const char *> mValidationLayers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> mDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME};

};
}
