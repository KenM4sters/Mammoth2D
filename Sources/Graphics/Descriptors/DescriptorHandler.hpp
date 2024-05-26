#pragma once
#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"

namespace Super 
{
class DescriptorHandler 
{
public:
    DescriptorHandler(std::vector<DescriptorSet>& sets);
    ~DescriptorHandler();

    inline DescriptorSet& GetDescriptorSet(uint32_t index) {return mDescriptorSets[index]; }

private:
    std::vector<DescriptorSet>& mDescriptorSets;
};
}