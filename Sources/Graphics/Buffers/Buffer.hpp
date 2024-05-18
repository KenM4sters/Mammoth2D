#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"

namespace Super 
{
class Buffer 
{
public: 
    Buffer(Device& device, VkDeviceSize deviceSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, const void* data = nullptr);
    virtual ~Buffer() 
    {
        vkDestroyBuffer(mDevice.GetDevice(), mBuffer, nullptr);
        vkFreeMemory(mDevice.GetDevice(), mBufferMemory, nullptr);
    }

    // Utility function to find the appropriate memory type that considers both the buffer and the
    // physical device.
    static uint32_t FindSuitableMemoryType(uint32_t typeFilter, const VkPhysicalDeviceMemoryProperties& memProperties, const VkMemoryPropertyFlags& requiredProperties);

    // Memory Management
    //
    void MapMemory(void** data);
    void UnMapMemory();

    // Getters
    //
    inline const VkBuffer& GetBuffer() const { return mBuffer; }
    inline const VkDeviceMemory& GetBufferMemory() const { return mBufferMemory; }
    inline VkDeviceSize& GetSize() { return mSize; }


protected:
    Device& mDevice;
    VkBuffer mBuffer = VK_NULL_HANDLE;
    VkDeviceMemory mBufferMemory = VK_NULL_HANDLE;
    VkDeviceSize mSize{0};
};
}