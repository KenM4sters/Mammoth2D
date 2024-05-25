#pragma once
#include <vulkan/vulkan.hpp>
namespace Super 
{
class Constant 
{
public:
    Constant(TexturePushConstant data, VkDeviceSize size, uint32_t offset, VkShaderStageFlags stages)
        : mData{data} 
    {
        mPushConstantRange.size = size;
        mPushConstantRange.offset = offset;
        mPushConstantRange.stageFlags = stages;
    }
    ~Constant() {}

    inline TexturePushConstant* GetData() { return &mData; }
    inline const VkPushConstantRange& GetPushConstantRange() const { return mPushConstantRange; } 

private:

    TexturePushConstant mData;

    VkPushConstantRange mPushConstantRange{};
};
}