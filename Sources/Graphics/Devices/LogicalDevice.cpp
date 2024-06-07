#include "LogicalDevice.hpp"

#include <set>

namespace mt 
{

LogicalDevice::LogicalDevice(PhysicalDevice& physicalDevice)
    : mPhysicalDevice{physicalDevice}
{

}

LogicalDevice::~LogicalDevice() 
{

}


void LogicalDevice::CreateLogicalDevice() 
{

    auto indices = mPhysicalDevice.GetQueueFamilyIndices();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) 
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(mPhysicalDevice.GetDeviceExtensions().size());
    createInfo.ppEnabledExtensionNames = mPhysicalDevice.GetDeviceExtensions().data();

    // might not really be necessary anymore because device specific validation layers
    // have been deprecated
    if (mPhysicalDevice.GetInstance().mEnableValidationLayers) 
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(mPhysicalDevice.GetInstance().GeValidationLayers().size());
        createInfo.ppEnabledLayerNames = mPhysicalDevice.GetInstance().GeValidationLayers().data();
    } 
    else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(mPhysicalDevice.GetPhysicalDevice(), &createInfo, nullptr, &mLogicalDevice) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(mLogicalDevice, indices.graphicsFamily, 0, &mGraphicsQueue);
    vkGetDeviceQueue(mLogicalDevice, indices.presentFamily, 0, &mPresentQueue);
}

void LogicalDevice::CreateCommandPool() 
{
    auto indices = mPhysicalDevice.GetQueueFamilyIndices();

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = indices.graphicsFamily;
    poolInfo.flags =
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(mLogicalDevice, &poolInfo, nullptr, &mCommandPool) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create command pool!");
    }
}


}