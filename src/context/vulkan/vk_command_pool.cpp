#include "CommandPool.hpp"

namespace mt 
{
CommandPool::CommandPool(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice)
    : mLogicalDevice{logicalDevice}
{
    CreateCommandPool(physicalDevice);
}

CommandPool::~CommandPool() 
{
    vkDestroyCommandPool(mLogicalDevice.GetDevice(), mCommandPool, nullptr);
}

void CommandPool::CreateCommandPool(PhysicalDevice& physicalDevice) 
{
    auto indices = physicalDevice.GetQueueFamilyIndices();

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = indices.graphicsFamily;
    poolInfo.flags =
        VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(mLogicalDevice.GetDevice(), &poolInfo, nullptr, &mCommandPool) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

}