#ifndef MAMMOTH_2D_UNIFORM_BUFFER_HPP
#define MAMMOTH_2D_UNIFORM_BUFFER_HPP

#include "Buffer.hpp"

namespace mt 
{
class UniformBuffer : public Buffer 
{
public:
    UniformBuffer(Device& device, VkDeviceSize size);
    UniformBuffer(Device& device, VkDeviceSize size, VkBufferUsageFlags usage, void* data = nullptr);

    ~UniformBuffer();

    void Update(const void* newData);
};
}

#endif