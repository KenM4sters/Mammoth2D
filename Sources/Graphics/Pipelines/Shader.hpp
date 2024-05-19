#pragma once
#include <vulkan/vulkan.hpp>
#include "Device.hpp"

namespace Super 
{
class Shader 
{
public:
    Shader(Device& device, const char* vertSrc, const char* fragSrc);
    ~Shader();


    const std::vector<char> ReadFromFile(const char* filePath) const;

    // Getters
    inline const std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() const {return mStages; } 

private:
    void CreateShaderModule(const std::vector<char> code, VkShaderModule* module);
    void CreateShaderStages(const char* vertSrc, const char* fragSrc);

    Device& mDevice;
    
    VkShaderModule mVertexModule = VK_NULL_HANDLE;
    VkShaderModule mFragmentModule = VK_NULL_HANDLE;
    
    std::vector<VkPipelineShaderStageCreateInfo> mStages{};
};
}