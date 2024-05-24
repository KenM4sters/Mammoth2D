#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"
#include "VertexInput.hpp"
#include "Uniform.hpp"

namespace Super 
{
class Shader 
{
public:
    Shader(Device& device, const char* vertSrc, const char* fragSrc, VertexInput vertexInput, Uniform uniform);
    ~Shader();


    const std::vector<char> ReadFromFile(const char* filePath) const;

    // Getters
    inline const std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() const {return mStages; } 
    inline const VertexInput& GetVertexInput() const {return mVertexInput; } 
    inline const Uniform& GetUniform() const {return mUniform; } 

private:
    void CreateShaderModule(const std::vector<char> code, VkShaderModule* module);
    void CreateShaderStages(const char* vertSrc, const char* fragSrc);

    Device& mDevice;

    VkShaderModule mVertexModule = VK_NULL_HANDLE;
    VkShaderModule mFragmentModule = VK_NULL_HANDLE;
    std::vector<VkPipelineShaderStageCreateInfo> mStages{};

    VertexInput mVertexInput;
    Uniform mUniform;
};
}