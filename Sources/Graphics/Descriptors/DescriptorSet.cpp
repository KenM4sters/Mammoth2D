#include "DescriptorSet.hpp"
#include "Logging.hpp"
#include <stdexcept>

namespace Super 
{

DescriptorSet::DescriptorSet(Device& device, Pipeline* pipeline)
    : mDevice{device}, mPipelineLayout{pipeline->GetPipelineLayout()}, mDescriptorPool{pipeline->GetDecsriptorPool()}, mPipelineBindPoint{pipeline->GetPipelineBindPoint()}
{
    VkDescriptorSetLayout descriptorLayout[1] = {pipeline->GetDescriptorSetLayout()};

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = mDescriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = descriptorLayout;


    if(vkAllocateDescriptorSets(mDevice.GetDevice(), &allocInfo, &mDescriptorSet) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }
}

DescriptorSet::~DescriptorSet() 
{
    // Desciptor sets are automatically destroyed by vulkan when the descriptor pool
    // is destroyed by the Pipeline class.
}

void DescriptorSet::Bind(VkCommandBuffer commandBuffer) 
{
    vkCmdBindDescriptorSets(commandBuffer, mPipelineBindPoint, mPipelineLayout, 0, 1, &mDescriptorSet, 0, nullptr);
}


}