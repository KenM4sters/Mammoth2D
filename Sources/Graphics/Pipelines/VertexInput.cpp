#include "VertexInput.hpp"

namespace Super 
{
VertexInput::VertexInput(std::unique_ptr<BufferLayout> bufferLayout) 
{
    VkVertexInputBindingDescription bindingDesc{};
    bindingDesc.binding = 0;
    bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindingDesc.stride = bufferLayout->GetBufferStride();

    mBindingDescriptions.push_back(bindingDesc);

    const auto& attribs = bufferLayout->GetAttributes();

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

VertexInput::~VertexInput() 
{

}

}