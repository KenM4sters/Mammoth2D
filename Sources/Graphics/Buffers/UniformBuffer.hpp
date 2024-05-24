#pragma once
#include "Buffer.hpp"

namespace Super 
{
class UniformBuffer : public Buffer 
{
public:
    UniformBuffer(Device& device, VkDeviceSize size, uint32_t offset, void* data = nullptr);
    ~UniformBuffer();

    void SetDescriptorBufferInfo(uint32_t offset, uint32_t size);

    const VkDescriptorBufferInfo& GetDescriptorInfo() const { return mBufferInfo; }

    void Update(const void* newData);

private:
    VkDescriptorBufferInfo mBufferInfo{};
};
}