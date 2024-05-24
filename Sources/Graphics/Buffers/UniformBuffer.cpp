#include "UniformBuffer.hpp"
#include <cassert>

namespace Super 
{

UniformBuffer::UniformBuffer(Device& device, VkDeviceSize size, uint32_t offset, void* data)
    : Buffer(device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data)
{
}

UniformBuffer::~UniformBuffer() 
{
    
}

void UniformBuffer::SetDescriptorBufferInfo(uint32_t offset, uint32_t size) 
{
    mBufferInfo.buffer = mBuffer;
    mBufferInfo.offset = offset;
    mBufferInfo.range = size;
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