#include "UniformBuffer.hpp"
#include <cassert>

namespace mt 
{

UniformBuffer::UniformBuffer(Device& device, VkDeviceSize size)
    : Buffer(device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, nullptr)
{
}

UniformBuffer::UniformBuffer(Device& device, VkDeviceSize size, VkBufferUsageFlags usage, void* data)
    : Buffer(device, size, usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data)
{
}
  
UniformBuffer::~UniformBuffer() 
{
    
}


void UniformBuffer::Update(const void* newData) 
{
    // Making sure the the newData actually points to something to update the UBO with.
    assert(newData && "Attempting to update uniform buffer with a nullptr!");

    void* data = nullptr;
    MapMemory(&data);
    std::memcpy(data, newData, static_cast<size_t>(mSize));
    UnMapMemory();
}

}