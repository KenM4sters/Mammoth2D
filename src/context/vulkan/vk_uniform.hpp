#ifndef MAMMOTH_2D_UNIFORM_HPP
#define MAMMOTH_2D_UNIFORM_HPP

#include "Device.hpp"
#include "Graphics/Buffers/UniformBuffer.hpp"

#include <glm/glm.hpp>

namespace mt 
{

template <class T>
class Uniform 
{
public:
    Uniform(Device& device, VkShaderStageFlags stage, uint32_t binding, void* data);
    ~Uniform() {}

    inline const uint32_t& GetBinding() const { return mBinding; }
    
    inline const VkShaderStageFlags& GetShaderStage() const { return mStage; }

private:
    Device& mDevice;

    std::shared_ptr<UniformBuffer> mBuffer = nullptr;

    VkShaderStageFlags mStage;
    uint32_t mBinding;

    void* mData = nullptr;
};
}

#endif