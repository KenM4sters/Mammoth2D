#pragma once 
#include <vulkan/vulkan.hpp>
#include "Graphics/Buffers/BufferLayout.hpp"

namespace Super 
{
class VertexInput 
{
public:
    VertexInput(BufferLayout& bufferLayout) 
    {
        VkVertexInputBindingDescription bindingDesc{};
        bindingDesc.binding = 0;
        bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        bindingDesc.stride = bufferLayout.GetBufferStride();

        mBindingDescriptions.push_back(bindingDesc);

        const auto& attribs = bufferLayout.GetAttributes();

        for(int i = 0; i < attribs.size(); i++) 
        {
            VkVertexInputAttributeDescription attribDesc;
            attribDesc.binding = i;
            attribDesc.format = attribs[i].GetFormat();
            attribDesc.offset = attribs[i].mOffset;
            attribDesc.location = attribs[i].GetShaderLocation();

            mAttribDescriptions.push_back(attribDesc);
        }
    }
    ~VertexInput() {}

    inline const std::vector<VkVertexInputBindingDescription>& GetBindingDescriptions() const { return mBindingDescriptions; }
    inline const std::vector<VkVertexInputAttributeDescription>& GetAttribDescriptions() const { return mAttribDescriptions; }

private:
    std::vector<VkVertexInputBindingDescription> mBindingDescriptions{};
    std::vector<VkVertexInputAttributeDescription> mAttribDescriptions{};
};
}