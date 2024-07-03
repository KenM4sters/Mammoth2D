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

// Helper Functions for interacting with buffers from outside of this class.
//----------------------------------------------------------------
uint32_t LogicalDevice::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const
{
    VkPhysicalDeviceMemoryProperties memProperties;

    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice.GetPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) 
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) 
        {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

VkFormat LogicalDevice::FindSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const
{
  for (VkFormat format : candidates) 
  {
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(mPhysicalDevice.GetPhysicalDevice(), format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) 
    {
      return format;
    } 
    else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) 
    {
      return format;
    }
  }
  throw std::runtime_error("failed to find supported format!");
}

void LogicalDevice::CreateBuffer(
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer &buffer,
    VkDeviceMemory &bufferMemory) 
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(mLogicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(mLogicalDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(mLogicalDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(mLogicalDevice, buffer, bufferMemory, 0);
}

void LogicalDevice::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, 
    uint32_t height, uint32_t layerCount) 
{
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = layerCount;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region);
        
    EndSingleTimeCommands(commandBuffer);
}

void LogicalDevice::CreateImageFromInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties,
    VkImage &image, VkDeviceMemory &imageMemory) const 
{
  if (vkCreateImage(mLogicalDevice, &imageInfo, nullptr, &image) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(mLogicalDevice, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(mLogicalDevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to allocate image memory!");
  }

  if (vkBindImageMemory(mLogicalDevice, image, imageMemory, 0) != VK_SUCCESS) 
  {
    throw std::runtime_error("failed to bind image memory!");
  }
}

void LogicalDevice::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) 
{
  VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

  VkBufferCopy copyRegion{};
  copyRegion.srcOffset = 0;  // Optional
  copyRegion.dstOffset = 0;  // Optional
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  EndSingleTimeCommands(commandBuffer);
}

VkCommandBuffer LogicalDevice::BeginSingleTimeCommands() 
{
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = mCommandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer;
  vkAllocateCommandBuffers(mLogicalDevice, &allocInfo, &commandBuffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(commandBuffer, &beginInfo);
  return commandBuffer;
}

void LogicalDevice::EndSingleTimeCommands(VkCommandBuffer commandBuffer) 
{
  vkEndCommandBuffer(commandBuffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  vkQueueSubmit(mGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(mGraphicsQueue);

  vkFreeCommandBuffers(mLogicalDevice, mCommandPool, 1, &commandBuffer);
}
//----------------------------------------------------------------



}