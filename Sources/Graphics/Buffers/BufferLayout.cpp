#include <stdexcept>
#include "BufferLayout.hpp"

namespace Super 
{
      
std::vector<float> SQUARE_VERTICES = 
{      
    0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f, 1.0f
};   

void SetVertexBufferFromVertices(Device& device, VkBuffer& buffer, VkDeviceMemory& deviceMemory, const std::vector<float>& vertices) 
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = vertices.size()*sizeof(float);
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(device.GetDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create vertex buffer!");
    }

    VkMemoryRequirements requirements;
    vkGetBufferMemoryRequirements(device.GetDevice(), buffer, &requirements);

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(device.GetPhysicalDevice(), &memProperties);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = requirements.size;
    allocInfo.memoryTypeIndex = FindSutiableMemoryType(
        requirements.memoryTypeBits, 
        &memProperties, 
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    );

    if(vkAllocateMemory(device.GetDevice(), &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to allocate memory for vertex buffer!");
    }

    vkBindBufferMemory(device.GetDevice(), buffer, deviceMemory, 0);

    void* data;
    vkMapMemory(device.GetDevice(), deviceMemory, 0, bufferInfo.size, 0, &data);

    memcpy(data, vertices.data(), (size_t)bufferInfo.size);

    vkUnmapMemory(device.GetDevice(), deviceMemory);

}


uint32_t FindSutiableMemoryType(uint32_t typeFilter, VkPhysicalDeviceMemoryProperties* memProperties, VkMemoryPropertyFlags properties) 
{

    for (uint32_t i = 0; i < memProperties->memoryTypeCount; i++) 
    {
        if ((typeFilter & (1 << i)) && (memProperties->memoryTypes[i].propertyFlags & properties) == properties) 
        {
            return i;
        }
    }
    throw std::runtime_error("failed to find suitable memory type!");
}

}