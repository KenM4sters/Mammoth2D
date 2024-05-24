#pragma once
#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"

namespace Super 
{
class DescriptorHandler 
{
public:
    DescriptorHandler(DescriptorSet descriptorSet);
    ~DescriptorHandler();

    inline const DescriptorSet* GetDescriptorSet() const {return &mDescriptorSet; }

private:
   DescriptorSet mDescriptorSet;
};
}