#include "Image.hpp"
#include "Logging.hpp"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <Stbi_image/stb_image.h>

namespace Super 
{
Image::Image(Device& device, std::string imagePath) 
    : mDevice{device}
{

    stbi_set_flip_vertically_on_load(true);

    int width, height, nChannels;
    stbi_uc* data = stbi_load(imagePath.c_str(), &width, &height, &nChannels, STBI_rgb_alpha);

    VkDeviceSize imageSize = width * height * 4;

    if(!data) 
    {
        throw std::runtime_error("Failed to load image from stbi_load()!");
    }

    mImageBuffer = std::make_unique<UniformBuffer>(
        mDevice,
        imageSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, // required by the spec since we're copying this buffer.
        (void*)data
    );

    vkBindBufferMemory(mDevice.GetDevice(), mImageBuffer->GetBuffer(), mImageBuffer->GetBufferMemory(), 0);

    stbi_image_free(data);

    CreateImage(width, height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, 
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mImage, mImageMemory);

    mImageBuffer->SetDescriptorImageInfo(mImageSampler, mImageView);
}

Image::~Image() 
{
    vkDestroyImage(mDevice.GetDevice(), mImage, nullptr);
    vkFreeMemory(mDevice.GetDevice(), mImageMemory, nullptr);
    vkDestroyImageView(mDevice.GetDevice(), mImageView, nullptr);
    vkDestroySampler(mDevice.GetDevice(), mImageSampler, nullptr);
    // Buffer class cleans up the buffer and memory resources.
}


void Image::CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) 
{
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(width);
    imageInfo.extent.height = static_cast<uint32_t>(height);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateImage(mDevice.GetDevice(), &imageInfo, nullptr, &mImage) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create image!");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(mDevice.GetDevice(), image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = mDevice.FindMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(mDevice.GetDevice(), &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate image memory!");
    }

    vkBindImageMemory(mDevice.GetDevice(), image, imageMemory, 0);

    // Now that the image is created, we need to transition its layout
    // to something that's more optimal for our use case - as a readonly buffer
    // shaders.
    //
    // Firstly, we tranition the image layout from undefined to the intermediate
    // "TRANSFER_DST_OPTIMAL" layout.
    TransitionImageLayout(mImage, VK_FORMAT_R8G8B8A8_SRGB, 
        VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    CopyBufferToImage(mImageBuffer->GetBuffer(), mImage, 
        static_cast<uint32_t>(width), static_cast<uint32_t>(height));

    // Lastly, we transition the image layout to the layout type that's most optimal
    // to be used as read only by the shaders.
    TransitionImageLayout(mImage, VK_FORMAT_R8G8B8A8_SRGB, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);


    // Next, we create the imageView that will be used by descriptor sets.
    CreateTextureImageView(format);
}

void Image::CreateTextureImageView(VkFormat format) 
{
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = mImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if(vkCreateImageView(mDevice.GetDevice(), &viewInfo, nullptr, &mImageView) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create texture image view!");
    }

    CreateTextureSampler();
}

void Image::CreateTextureSampler() 
{
    VkPhysicalDeviceProperties properties{};

    vkGetPhysicalDeviceProperties(mDevice.GetPhysicalDevice(), &properties);

    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    // This may not be available on all devices, but in Device.cpp we already make
    // sure that the device does support anisotropy. 
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1.0f;

    if(vkCreateSampler(mDevice.GetDevice(), &samplerInfo, nullptr, &mImageSampler) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create image sampler!");
    }
}



// Utility functions.
//
VkCommandBuffer Image::BeginSingleTimeCommands() 
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice.GetCommandPool();
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(mDevice.GetDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void Image::EndSingleTimeCommands(VkCommandBuffer commandBuffer) 
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(mDevice.GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(mDevice.GetGraphicsQueue());

    vkFreeCommandBuffers(mDevice.GetDevice(), mDevice.GetCommandPool(), 1, &commandBuffer);
}

void Image::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) 
{
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.srcAccessMask = 0; // TODO
    barrier.dstAccessMask = 0; // TODO

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
    {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } 
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } 
    else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage,
        0, 0, nullptr, 0, nullptr, 1, &barrier);

    EndSingleTimeCommands(commandBuffer);
}

void Image::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) 
{
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = 
    {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    EndSingleTimeCommands(commandBuffer);
}


}