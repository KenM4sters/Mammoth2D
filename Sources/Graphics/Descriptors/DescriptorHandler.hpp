#pragma once
#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"

namespace Super 
{
class DescriptorHandler 
{
public:
    DescriptorHandler(DescriptorSet sets[2]);
    ~DescriptorHandler();

    // void AllocateDescriptorSet(DescriptorSet& descriptorSet);

    inline DescriptorSet& GetDescriptorSet(uint32_t index) {return mDescriptorSets[index]; }

private:
    std::vector<DescriptorSet> mDescriptorSets;
};
}