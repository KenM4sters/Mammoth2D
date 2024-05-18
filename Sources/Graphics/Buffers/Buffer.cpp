#include "Buffer.hpp"

namespace Super 
{
Buffer::Buffer(Device& device, VkDeviceSize deviceSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, const void* data)
    : mDevice{device}, mSize{deviceSize}
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = mSize;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(device.GetDevice(), &bufferInfo, nullptr, &mBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create vertex buffer!");
    }

    VkMemoryRequirements requirements;
    vkGetBufferMemoryRequirements(device.GetDevice(), mBuffer, &requirements);

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(device.GetPhysicalDevice(), &memProperties);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = requirements.size;
    allocInfo.memoryTypeIndex = FindSuitableMemoryType(
        requirements.memoryTypeBits, 
        memProperties, 
        properties
    );

    if(vkAllocateMemory(device.GetDevice(), &allocInfo, nullptr, &mBufferMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to allocate memory for vertex buffer!");
    }

    if(data) 
    {
        void* mapped = nullptr;
        MapMemory(&mapped);

        memcpy(mapped, data, static_cast<size_t>(mSize));

        UnMapMemory();
    }
}


// Utility function to find the appropriate memory type that considers both the buffer and the
// physical device.
uint32_t Buffer::FindSuitableMemoryType(const uint32_t typeFilter, const VkPhysicalDeviceMemoryProperties& memProperties,  const VkMemoryPropertyFlags& requiredProperties) 
{
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) 
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & requiredProperties) == requiredProperties) 
        {
            return i;
        }
    }
    throw std::runtime_error("failed to find suitable memory type!");
}


// Memory Management
//
void Buffer::MapMemory(void** data) 
{
    vkMapMemory(mDevice.GetDevice(), mBufferMemory, 0, mSize, 0, data);
}

void Buffer::UnMapMemory() 
{
    vkUnmapMemory(mDevice.GetDevice(), mBufferMemory);
}

}