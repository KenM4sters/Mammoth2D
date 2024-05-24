#pragma once
#include "Buffer.hpp"

namespace Super 
{
class UniformBuffer : public Buffer 
{
public:
    UniformBuffer(Device& device, VkDeviceSize size, uint32_t offset);
    UniformBuffer(Device& device, VkDeviceSize size, VkBufferUsageFlags usage, void* data = nullptr);

    ~UniformBuffer();

    void SetDescriptorBufferInfo(uint32_t offset, uint32_t size);
    VkDescriptorBufferInfo& GetDescriptorBufferInfo() { return mBufferInfo; }

    void SetDescriptorImageInfo(VkSampler sampler, VkImageView imageView);
    VkDescriptorImageInfo& GetDescriptorImageInfo() { return mImageInfo; }

    void Update(const void* newData);

private:
    VkDescriptorBufferInfo mBufferInfo{};
    VkDescriptorImageInfo mImageInfo{};
};
}