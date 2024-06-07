#ifndef MAMMOTH_2D_LOGICAL_DEVICE_HPP
#define MAMMOTH_2D_LOGICAL_DEVICE_HPP

#include "Graphics/Renderer/SwapChain.hpp"
#include "PhysicalDevice.hpp"


namespace mt 
{

/**
 * @brief TBC
*/
class LogicalDevice 
{
public:
    LogicalDevice(PhysicalDevice& physicalDevice);
    ~LogicalDevice();

    inline const VkDevice& GetLogicalDevice() const { return mLogicalDevice; }
    inline const VkQueue& GetPresentQueue() const { return mPresentQueue; }
    inline const VkQueue& GetGraphicsQueue() const { return mGraphicsQueue; }
    inline const VkCommandPool& GetCommandPool() const { return mCommandPool; }

private:
    void CreateLogicalDevice();
    void CreateCommandPool();


private:
    PhysicalDevice& mPhysicalDevice;

    VkDevice mLogicalDevice = VK_NULL_HANDLE;

    VkCommandPool mCommandPool = VK_NULL_HANDLE;

    VkQueue mGraphicsQueue = VK_NULL_HANDLE;
    VkQueue mPresentQueue = VK_NULL_HANDLE;
};
}

#endif