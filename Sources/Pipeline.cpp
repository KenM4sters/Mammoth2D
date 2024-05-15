#include <cassert>
#include <iostream>

#include "Pipeline.hpp"

namespace Super 
{
Pipeline::Pipeline(std::shared_ptr<Device> device, Pipeline_Desc desc, const char* vertSrc, const char* fragSrc)
    : mDevice{device}
{
    CreateGraphicsPipeline(desc, vertSrc, fragSrc);
}

Pipeline::~Pipeline() 
{

}

const std::vector<char> Pipeline::ReadFromFile(const char* filePath) const 
{
    std::ifstream file{filePath, std::ios::ate | std::ios::binary};

    assert(file.is_open() && "File could not be opened!"); // check for errors - if thrown, double check file path.

    size_t fileSize = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void Pipeline::CreateGraphicsPipeline(Pipeline_Desc& desc, const char* vertSrc, const char* fragSrc) 
{
    auto vertCode = ReadFromFile(vertSrc);
    auto fragCode = ReadFromFile(fragSrc);

    std::cout << vertCode.size() << std::endl;
    std::cout << fragCode.size() << std::endl;
}

void Pipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) 
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.codeSize = code.size();
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if(vkCreateShaderModule(mDevice->GetDevice(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create shader module!");
    }

}

Pipeline_Desc Pipeline::DefaultPipelineDesc(uint32_t width, uint32_t height) 
{
    Pipeline_Desc desc{};

    return desc;
}


}