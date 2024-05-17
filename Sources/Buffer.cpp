#include "Buffer.hpp"

namespace Super 
{
std::vector<float> SQUARE_VERTICES = 
{
    0.0f, -1.0f, // top-left
    1.0f, 0.0f, // bottom-right
    0.0f, 0.0f, // bottom-left 

    0.0f, -1.0f, // top-left   
    1.0f, -1.0f, // top-right
    1.0f, 0.0f, // bottom-right
};

void SetVertexBufferFromVertices(std::shared_ptr<Device>& device, VkBuffer* buffer, const std::vector<float>& vertices) 
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = vertices.size()*sizeof(float);
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(device->GetDevice(), &bufferInfo, nullptr, &(*buffer)) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create vertex buffer!");
    }
}
}