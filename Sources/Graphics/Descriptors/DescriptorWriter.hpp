#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>
#include "DescriptorHandler.hpp"

namespace Super 
{
class DescriptorWriter 
{
public:
    DescriptorWriter()
    {
        
    }

    ~DescriptorWriter() 
    {

    }

    void WriteToBuffer(uint32_t index, uint32_t binding, VkDescriptorBufferInfo& bufferInfo, DescriptorSet& descriptorSet) 
    {
        mWriteDescriptor[index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        mWriteDescriptor[index].dstSet = descriptorSet.GetDescriptorSet();
        mWriteDescriptor[index].dstBinding = binding;
        mWriteDescriptor[index].dstArrayElement = 0;
        mWriteDescriptor[index].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        mWriteDescriptor[index].descriptorCount = 1;
        mWriteDescriptor[index].pBufferInfo = &bufferInfo;
        mWriteDescriptor[index].pImageInfo = nullptr;
        mWriteDescriptor[index].pTexelBufferView = nullptr;
    }

    void WriteToBuffer(uint32_t index, uint32_t binding, VkDescriptorImageInfo& imageInfo, DescriptorSet& descriptorSet) 
    {
        mWriteDescriptor[index].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        mWriteDescriptor[index].dstSet = descriptorSet.GetDescriptorSet();
        mWriteDescriptor[index].dstBinding = binding;
        mWriteDescriptor[index].dstArrayElement = 0;
        mWriteDescriptor[index].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        mWriteDescriptor[index].descriptorCount = 1;
        mWriteDescriptor[index].pBufferInfo = nullptr;
        mWriteDescriptor[index].pImageInfo = &imageInfo;
        mWriteDescriptor[index].pTexelBufferView = nullptr;
    }

    void UpdateDescriptorSet(Device& device) 
    {
        vkUpdateDescriptorSets(device.GetDevice(), mWriteDescriptor.size(), mWriteDescriptor.data(), 0, nullptr);
    }

private:
    std::vector<VkWriteDescriptorSet> mWriteDescriptor{6};
};
}