#pragma once
#include <vulkan/vulkan.hpp>



namespace mt 
{

template<class T>
class Constant 
{
public:
    Constant(T data, VkDeviceSize size, VkShaderStageFlags stages)
        : mData{data} 
    {
        mPushConstantRange.size = size;
        mPushConstantRange.offset = 0;
        mPushConstantRange.stageFlags = stages;
    }
    ~Constant() {}

    inline TexturePushConstant* GetData() { return &mData; }
    
    inline const VkPushConstantRange& GetPushConstantRange() const { return mPushConstantRange; } 

private:
    VkPushConstantRange mPushConstantRange{};
};
}