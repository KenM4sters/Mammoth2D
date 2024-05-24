#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"
namespace Super 
{
class Uniform 
{
public:
    Uniform(uint32_t binding = 0, uint32_t size = 0, uint32_t offset = 0, VkShaderStageFlags flags = VK_SHADER_STAGE_VERTEX_BIT)
        : mBinding{binding}, mSize{size}, mOffset{offset}, mFlags{flags} 
    {

    }
    ~Uniform() {}

    inline const uint32_t& GetBinding() const { return mBinding; }
    inline const uint32_t& GetSize() const { return mSize;} 
    inline const uint32_t& GetOffset() const { return mOffset; }
    inline const VkShaderStageFlags& GetFlags() const { return mFlags; } 

private:
    uint32_t mBinding;
    uint32_t mSize; 
    uint32_t mOffset;
    VkShaderStageFlags mFlags;

};
}