#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"
#include "VertexInput.hpp"
#include "Uniform.hpp"
#include "Constant.hpp"

#include <Cross/spirv_glsl.hpp>

namespace mt 
{
class Shader 
{
public:
    Shader(Device& device, const char* vertSrc, const char* fragSrc);

    ~Shader();

    inline const std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() const {return mStages; } 

    static void ParseGLSL(const char* filePath);

private:
    const std::vector<char> ReadFromFile(const char* filePath) const;

    void CreateShaderModule(const std::vector<char> code, VkShaderModule* module);

    void CreateShaderStages(const char* vertSrc, const char* fragSrc);

private:
    Device& mDevice;

    VkShaderModule mVertexModule = VK_NULL_HANDLE;
    VkShaderModule mFragmentModule = VK_NULL_HANDLE;
    std::vector<VkPipelineShaderStageCreateInfo> mStages{};
};
}