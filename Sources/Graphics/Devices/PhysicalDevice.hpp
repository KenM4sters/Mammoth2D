#ifndef MAMMOTH_2D_PHYSICAL_DEVICE_HPP
#define MAMMOTH_2D_PHYSICAL_DEVICE_HPP

#include "Graphics/Renderer/SwapChain.hpp"
#include "Instance.hpp"

namespace mt 
{

/**
 * @brief TBC
*/
class PhysicalDevice 
{
public:
    PhysicalDevice(Window& window, const Instance& instance);
    ~PhysicalDevice();

    inline const VkPhysicalDevice& GetPhysicalDevice() const { return mPhysicalDevice; }
    inline const Instance& GetInstance() const { return mInstance; }
    inline const QueueFamilyIndices& GetQueueFamilyIndices() const { return mQueueFamilyIndices; }
    const std::vector<const char*>& GetDeviceExtensions() const { return mDeviceExtensions; }

private:
    void CreateWindowSurface();
    void ChoosePhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device); 
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails CheckSwapChainSupport(VkPhysicalDevice device); 


private:
    Window& mWindow;

    const Instance& mInstance;

    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties mPhysicalDeviceProps{};
    VkPhysicalDeviceFeatures mFeatures{};
    VkPhysicalDeviceMemoryProperties mMemoryProperties{};

    VkSurfaceKHR mSurface = VK_NULL_HANDLE;

    SwapChainSupportDetails mSwapChainSupportDetails{};
    QueueFamilyIndices mQueueFamilyIndices{};

    const std::vector<const char *> mDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME};

};
}

#endif