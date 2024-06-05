#ifndef MAMMOTH_2D_DESCRIPTOR_SET_HPP
#define MAMMOTH_2D_DESCRIPTOR_SET_HPP

#include "Device.hpp"
#include "Graphics/Pipelines/Pipeline.hpp"

#include <vector>

namespace mt 
{
class DescriptorSet 
{
public:
    DescriptorSet(Device& device, Pipeline* pipeline);
    ~DescriptorSet();

    inline const VkDescriptorSet GetDescriptorSet() const { return mDescriptorSet; }

    void Bind(VkCommandBuffer commandBuffer);

private:    
    Device& mDevice;

    VkPipelineLayout mPipelineLayout;
    VkPipelineBindPoint mPipelineBindPoint;
    VkDescriptorPool mDescriptorPool;
    VkDescriptorSet mDescriptorSet = VK_NULL_HANDLE;
};
}

#endif