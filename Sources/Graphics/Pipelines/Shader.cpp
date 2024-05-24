#include "Shader.hpp"
#include <fstream>
#include <cassert>

namespace Super 
{
Shader::Shader(Device& device, const char* vertSrc, const char* fragSrc, VertexInput vertexInput, Uniform uniform)
    : mDevice{device}, mVertexInput{vertexInput}, mUniform{uniform}
{
    CreateShaderStages(vertSrc, fragSrc);
}

Shader::~Shader() 
{
    vkDestroyShaderModule(mDevice.GetDevice(), mVertexModule, nullptr);
    vkDestroyShaderModule(mDevice.GetDevice(), mFragmentModule, nullptr);
}

const std::vector<char> Shader::ReadFromFile(const char* filePath) const 
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

void Shader::CreateShaderModule(const std::vector<char> code, VkShaderModule* module) 
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.codeSize = code.size();
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if(vkCreateShaderModule(mDevice.GetDevice(), &createInfo, nullptr, module) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create shader module!");
    }
}


void Shader::CreateShaderStages(const char* vertSrc, const char* fragSrc) 
{
    auto vertCode = ReadFromFile(vertSrc);
    auto fragCode = ReadFromFile(fragSrc);


    CreateShaderModule(vertCode, &mVertexModule);
    CreateShaderModule(fragCode, &mFragmentModule);

    // Vertex shader.
    //
    VkPipelineShaderStageCreateInfo vertex{};
    vertex.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertex.module = mVertexModule;
    vertex.pName = "main";
    vertex.flags = 0;
    vertex.pSpecializationInfo = nullptr;
    vertex.pNext = nullptr;
    mStages.push_back(std::move(vertex));
    // Fragment shader.
    //
    VkPipelineShaderStageCreateInfo fragment{};
    fragment.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment.module = mFragmentModule;
    fragment.pName = "main";
    fragment.flags = 0;
    fragment.pSpecializationInfo = nullptr;
    fragment.pNext = nullptr;
    mStages.push_back(std::move(fragment));

}
}