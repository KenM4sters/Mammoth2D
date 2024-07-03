#include "Uniform.hpp"

namespace mt 
{

template<class T>
Uniform<T>::Uniform(Device& device, VkShaderStageFlags stage, uint32_t binding, void* data) 
    : mDevice{device}, mStage{stage}, mBinding{binding}, mData{data}
{
    mBuffer = std::make_unique<UniformBuffer>(
        mDevice,
        sizeof(T),
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        mData 
    );
}

}