#pragma once 
#include <vulkan/vulkan.hpp>
#include "Graphics/Buffers/BufferLayout.hpp"

namespace Super 
{
class VertexInput 
{
public:
    VertexInput(std::unique_ptr<BufferLayout> bufferLayout);
    ~VertexInput();

    inline const std::vector<VkVertexInputBindingDescription>& GetBindingDescriptions() const { return mBindingDescriptions; }
    inline const std::vector<VkVertexInputAttributeDescription>& GetAttribDescriptions() const { return mAttribDescriptions; }

private:
    std::vector<VkVertexInputBindingDescription> mBindingDescriptions{};
    std::vector<VkVertexInputAttributeDescription> mAttribDescriptions{};
};
}