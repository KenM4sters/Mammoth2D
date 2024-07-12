#ifndef MAMMOTH_2D_DESCRIPTOR_HANDLER_HPP
#define MAMMOTH_2D_DESCRIPTOR_HANDLER_HPP

#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"


namespace mt 
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

#endif