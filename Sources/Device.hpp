#pragma once
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_beta.h>
#include "Window.hpp"

namespace Super 
{

struct Swap_Chain_Support_Details {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct Queue_Family_Indices {
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;
  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

class Device 
{
public:
    Device(std::shared_ptr<Window>& window);
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
    
    // Even though we already run call these functions from within the implementation, we're choosing
    // not to store them within the class since they're not really required by all but a handful of
    // other classes, so we'll make getters for these private functions as well.
    //
    Swap_Chain_Support_Details GetSwapChainSupport() { return CheckSwapChainSupport(mPhysicalDevice); }
    Queue_Family_Indices FindPhysicalQueueFamilies() { return FindQueueFamilies(mPhysicalDevice); }

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
    Swap_Chain_Support_Details CheckSwapChainSupport(VkPhysicalDevice device) const;

    void ConfigureDebugMessengerCallback(VkDebugUtilsMessengerCreateInfoEXT& createInfo) const;
    
    Queue_Family_Indices FindQueueFamilies(VkPhysicalDevice device) const;

    const std::vector<const char*> GetAllRequiredExtensions() const;
    
    std::shared_ptr<Window> mWindow = nullptr;

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
