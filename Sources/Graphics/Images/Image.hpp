#ifndef MAMMOTH_2D_IMAGE_HPP
#define MAMMOTH_2D_IMAGE_HPP

#include <vulkan/vulkan.hpp>
#include "Graphics/Buffers/UniformBuffer.hpp"
#include "Device.hpp"

#include <string>

namespace mt 
{
class Image 
{
public:
    Image(Device& device, std::string imagePath);
    ~Image();

    // Getters
    //
    inline std::unique_ptr<UniformBuffer>& GetUniformBuffer() {return mImageBuffer; }

    // Utility functions for creating submitting commands before the main rendering loop
    // to change the image layout of an image.
    // note: "SingleTimeCommands" - this has no effect on the main rendering command buffer.
    //
    VkCommandBuffer BeginSingleTimeCommands();
    void EndSingleTimeCommands(VkCommandBuffer);
    void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:
    void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void CreateTextureImageView(VkFormat format);
    void CreateTextureSampler();
    Device& mDevice;

    std::unique_ptr<UniformBuffer> mImageBuffer = nullptr;

    VkImage mImage = VK_NULL_HANDLE;
    VkImageView mImageView = VK_NULL_HANDLE;
    VkSampler mImageSampler = VK_NULL_HANDLE;
    VkDeviceMemory mImageMemory = VK_NULL_HANDLE;
};
}

#endif