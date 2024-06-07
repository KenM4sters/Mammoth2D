#include "PhysicalDevice.hpp"

#include <iostream>
#include <set>

namespace mt 
{

PhysicalDevice::PhysicalDevice(Window& window, const Instance& instance)
    : mWindow{window}, mInstance{instance}
{

}

PhysicalDevice::~PhysicalDevice() 
{

}

void PhysicalDevice::CreateWindowSurface() 
{
    mWindow.CreateWindowSurface(mInstance.GetInstance(), &mSurface);
}

void PhysicalDevice::ChoosePhysicalDevice() 
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(mInstance.GetInstance(), &deviceCount, nullptr);

    if (deviceCount == 0) 
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::cout << "Device count: " << deviceCount << std::endl;

    std::vector<VkPhysicalDevice> devices(deviceCount);

    vkEnumeratePhysicalDevices(mInstance.GetInstance(), &deviceCount, devices.data());

    for (const auto &device : devices) 
    {
        if (IsDeviceSuitable(device)) 
        {
            mPhysicalDevice = device;
            break;
        }
    }

    if (mPhysicalDevice == VK_NULL_HANDLE) 
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    vkGetPhysicalDeviceProperties(mPhysicalDevice, &mPhysicalDeviceProps);
    std::cout << "physical device: " << mPhysicalDeviceProps.deviceName << std::endl;
    std::cout << "max push constant size: " << mPhysicalDeviceProps.limits.maxPushConstantsSize << std::endl; 

}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)  
{
    mQueueFamilyIndices = FindQueueFamilies(device);

    bool extensionsSupported = CheckDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported) 
    {
        SwapChainSupportDetails swapChainSupport = CheckSwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    vkGetPhysicalDeviceFeatures(device, &mFeatures);

    return mQueueFamilyIndices.isComplete() && extensionsSupported && swapChainAdequate &&
            mFeatures.samplerAnisotropy;
}

QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkPhysicalDevice device)  
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies) 
    {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
        {
            indices.graphicsFamily = i;
            indices.graphicsFamilyHasValue = true;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, mSurface, &presentSupport);

        if (queueFamily.queueCount > 0 && presentSupport) 
        {
            indices.presentFamily = i;
            indices.presentFamilyHasValue = true;
        }

        if (indices.isComplete()) 
        {
            break;
        }
        
        i++;
    }

    return indices;
}

bool PhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)  
{
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(
        device,
        nullptr,
        &extensionCount,
        availableExtensions.data()
    );

    std::set<std::string> requiredExtensions(mDeviceExtensions.begin(), mDeviceExtensions.end());

    for (const auto &extension : availableExtensions) 
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

SwapChainSupportDetails PhysicalDevice::CheckSwapChainSupport(VkPhysicalDevice device)  
{
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, mSurface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, mSurface, &formatCount, nullptr);

    if (formatCount != 0) 
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, mSurface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, mSurface, &presentModeCount, nullptr);

    if (presentModeCount != 0) 
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            device,
            mSurface,
            &presentModeCount,
            details.presentModes.data()
        );
    }
    return details;
}

}