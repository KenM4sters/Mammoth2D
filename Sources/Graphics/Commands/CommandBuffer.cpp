#include "CommandBuffer.hpp"

namespace mt 
{

CommandBuffer::CommandBuffer(LogicalDevice& logicalDevice, CommandPool& commandPool)
    : mLogicalDevice{logicalDevice}, mCommandPool{commandPool}
{
    CreateCommandBufffer();
}

CommandBuffer::~CommandBuffer() 
{
    vkFreeCommandBuffers(mLogicalDevice.GetDevice(), 
        mCommandPool.GetCommandPool(), 1, &mCommandBuffer);
}

void CommandBuffer::CreateCommandBufffer() 
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mCommandPool.GetCommandPool();
    allocInfo.commandBufferCount = 1;

    if(vkAllocateCommandBuffers(mLogicalDevice.GetDevice(), &allocInfo, &mCommandBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create command buffers!");
    }
}

VkCommandBuffer CommandBuffer::Begin() 
{
    assert(!mIsRunning && "Can't begin a command buffer while already runnning!");

    mIsRunning = true;
    auto commandBuffer = GetCurrentCommandBuffer();

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }

    return commandBuffer;
}

const VkCommandBuffer& CommandBuffer::End() 
{
    assert(mIsRunning && "Can't call end frame while frame is not in progress!");
    
    if(vkEndCommandBuffer(mCommandBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to record command buffers!");
    }

    mIsRunning = false;

    return mCommandBuffer;
}

}