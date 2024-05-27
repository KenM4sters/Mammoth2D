#pragma once
#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"

namespace Super 
{
class DescriptorHandler 
{
public:
    DescriptorHandler(DescriptorSet set);
    ~DescriptorHandler();

    inline DescriptorSet& GetDescriptorSet() {return mDescriptorSet; }

private:
    DescriptorSet mDescriptorSet;
};
}