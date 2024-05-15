#pragma once
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
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
    Device();
    ~Device();

    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    VkPhysicalDeviceProperties mPhysicalDeviceProps;


private:

    void CreateInstance();
    void CreateSurface();
    void ChoosePhysicalDevice();
    void SetupDebugMessenger();

    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    bool CheckValidationLayerSupport() const;
    bool HasGLFWRequiredExtensions() const;
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
