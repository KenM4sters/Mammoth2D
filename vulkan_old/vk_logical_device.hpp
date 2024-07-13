#ifndef MAMMOTH_2D_LOGICAL_DEVICE_HPP
#define MAMMOTH_2D_LOGICAL_DEVICE_HPP

#include "Graphics/Renderer/SwapChain.hpp"
#include "PhysicalDevice.hpp"


namespace mt 
{

/**
 * @brief Wrapper for the VkDevice (The layer of abstraction that makes calls to the 
 * actual physical device, VkPhysicalDevice). 
*/
class LogicalDevice 
{
public:
    /**
     * @brief Constructs an instance of a LogicalDevice.
     * @param physicalDevice the appropriate physical device that we wish to make all 
     * command calls to. A PhysicalDevice should be properly established before constructing
     * this class.
    */
    LogicalDevice(PhysicalDevice& physicalDevice);
    ~LogicalDevice();

    inline const VkDevice& GetDevice() const { return mLogicalDevice; }
    inline const VkQueue& GetPresentQueue() const { return mPresentQueue; }
    inline const VkQueue& GetGraphicsQueue() const { return mGraphicsQueue; }

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

    VkFormat FindSupportedFormat(
        const std::vector<VkFormat> &candidates, 
        VkImageTiling tiling, 
        VkFormatFeatureFlags features
    ) const;

    void CreateBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer &buffer,
        VkDeviceMemory &bufferMemory
    );

    void CopyBufferToImage(
        VkBuffer buffer, 
        VkImage image, 
        uint32_t width, 
        uint32_t height, 
        uint32_t layerCount
    );

    void CreateImageFromInfo(
        const VkImageCreateInfo &imageInfo,
        VkMemoryPropertyFlags properties,
        VkImage &image,
        VkDeviceMemory &imageMemory
    ) const;

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    VkCommandBuffer BeginSingleTimeCommands();

    void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

private:
    /**
     * @brief Creates a VkDevice instance as well as a graphics and present queue.
    */
    void CreateLogicalDevice();

private:
    PhysicalDevice& mPhysicalDevice;

    VkDevice mLogicalDevice = VK_NULL_HANDLE;

    VkQueue mGraphicsQueue = VK_NULL_HANDLE;
    VkQueue mPresentQueue = VK_NULL_HANDLE;
};
}

#endif