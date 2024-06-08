#ifndef MAMMOTH_2D_PHYSICAL_DEVICE_HPP
#define MAMMOTH_2D_PHYSICAL_DEVICE_HPP

#include "Graphics/Renderer/SwapChain.hpp"
#include "Window.hpp"
#include "Instance.hpp"

namespace mt 
{

/**
 * @brief Wrapper for the actual VkPhysicalDevice (the GPU itself).
*/
class PhysicalDevice 
{
public:
    /**
     * @brief Constructs an instance of a PhysicalDevice.
     * @param window An instance of a window that a window surface will be created for.
     * @param instance a readonly instance of an Instance class which basically just describes
     * our vulkan runtime state (think debug callbacks, names etc...).
    */
    PhysicalDevice(Window& window, const Instance& instance);
    ~PhysicalDevice();

    inline const VkPhysicalDevice& GetPhysicalDevice() const { return mPhysicalDevice; }
    inline const Instance& GetInstance() const { return mInstance; }
    inline const VkSurfaceKHR& GetSurface() const { return mSurface; }
    inline const QueueFamilyIndices& GetQueueFamilyIndices() const { return mQueueFamilyIndices; }
    inline const std::vector<const char*>& GetDeviceExtensions() const { return mDeviceExtensions; }
    inline const SwapChainSupportDetails& GetSwapChainSupport() const { return mSwapChainSupportDetails; }
    
private:
    /**
     * @brief Simple call to the member function of the Window class that 
     * calls glfwCreatewindowSurface().
    */
    void CreateWindowSurface();
    
    /**
     * @brief Iterates through all of the physical devices that the vulkan api detects and
     * determines which one is optimal for our use case.
    */
    void ChoosePhysicalDevice();
    /**
     * @brief Helper function that's used by ChoosePhysicalDevice() to assess whether 
     * the physical device is actually suitable or not, given an array of dependancies.
     * @param device The physical device that we're checking against. 
    */
    bool IsDeviceSuitable(VkPhysicalDevice device);

    /**
     * @brief TODO.
    */
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device); 

    /**
     * @brief Checks whether the extensions that we need are support by the phsyical device
     * @param device The physical device that we're checking against. 
    */
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

    /**
     * @brief Checks whether the Swapchain supports the physical device.
     * @param device The physical device that we're checking against. 
    */
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