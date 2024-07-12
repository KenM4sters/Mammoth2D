#ifndef MAMMOTH_2D_DESCRIPTOR_WRITER_HPP
#define MAMMOTH_2D_DESCRIPTOR_WRITER_HPP

#include <vulkan/vulkan.hpp>
#include "DescriptorHandler.hpp"

#include <vector>

namespace mt 
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

    void WriteToImage(std::vector<VkDescriptorImageInfo>& imageInfo, DescriptorSet& descriptorSet) 
    {
        for(int i = 0; i < imageInfo.size(); i++)  
        {
            mWriteDescriptor[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            mWriteDescriptor[i].dstSet = descriptorSet.GetDescriptorSet();
            mWriteDescriptor[i].dstBinding = i;
            mWriteDescriptor[i].dstArrayElement = 0;
            mWriteDescriptor[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            mWriteDescriptor[i].descriptorCount = 1;
            mWriteDescriptor[i].pBufferInfo = nullptr;
            mWriteDescriptor[i].pImageInfo = &imageInfo[i];
            mWriteDescriptor[i].pTexelBufferView = nullptr;
        }
    }

    void UpdateDescriptorSet(Device& device) 
    {
        vkUpdateDescriptorSets(device.GetDevice(), mWriteDescriptor.size(), mWriteDescriptor.data(), 0, nullptr);
    }

private:
    std::vector<VkWriteDescriptorSet> mWriteDescriptor{6};
};
}

#endif