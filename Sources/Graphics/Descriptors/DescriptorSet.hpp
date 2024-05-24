#pragma once
#include <vector>
#include "Device.hpp"
#include "Graphics/Pipelines/Pipeline.hpp"

namespace Super 
{
class DescriptorSet 
{
public:
    DescriptorSet(Device& device, Pipeline& pipeline);
    ~DescriptorSet();

    inline const VkDescriptorSet GetDescriptorSet() const { return mDescriptorSet; }

private:    
    Device& mDevice;

    VkPipelineLayout mPipelineLayout;
    VkPipelineBindPoint mPipelineBindPoint;
    VkDescriptorPool mDescriptorPool;
    VkDescriptorSet mDescriptorSet = VK_NULL_HANDLE;
};
}