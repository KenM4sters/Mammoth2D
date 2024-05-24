#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>
#include "DescriptorHandler.hpp"

namespace Super 
{
class DescriptorWriter 
{
public:
    DescriptorWriter(DescriptorHandler& handler)
        : mDescriptorHandler{handler} 
    {
        
    }

    ~DescriptorWriter() 
    {

    }

    void WriteToBuffer(uint32_t binding, VkDescriptorBufferInfo& bufferInfo, uint32_t index) 
    {
        mWriteDescriptor.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        mWriteDescriptor.dstSet = mDescriptorHandler.GetDescriptorSet()->GetDescriptorSet();
        mWriteDescriptor.dstBinding = 0;
        mWriteDescriptor.dstArrayElement = 0;
        mWriteDescriptor.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        mWriteDescriptor.descriptorCount = 1;
        mWriteDescriptor.pBufferInfo = &bufferInfo;
        mWriteDescriptor.pImageInfo = nullptr;
        mWriteDescriptor.pTexelBufferView = nullptr;
    }

    void UpdateDescriptorSet(Device& device) 
    {
        vkUpdateDescriptorSets(device.GetDevice(), 1, &mWriteDescriptor, 0, nullptr);
    }

private:

    DescriptorHandler& mDescriptorHandler;

    VkWriteDescriptorSet mWriteDescriptor{};
};
}