#ifndef MAMMOTH_2D_COMMAND_BUFFER_HPP
#define MAMMOTH_2D_COMMAND_BUFFER_HPP


#include "Graphics/Devices/LogicalDevice.hpp"
#include "CommandPool.hpp"

namespace mt 
{

/**
 * @brief Wrapper for a vkCommandBuffer. Our application uses two of these since we're using
 * two fames in flight by default (meaning that we need to make 2 seperate commands to make
 * calls to for each different frame).
*/
class CommandBuffer 
{
public:
    /**
     * @brief Constructs a CommandBuffer instance.
     * @param logicalDevice a LogicalDevice instance.
     * @param commandPool a CommandPool instance.
    */
    CommandBuffer(LogicalDevice& logicalDevice, CommandPool& commandPool);

    ~CommandBuffer();

    /**
     * @brief Begins the VkCommandBuffer member instance so that any following commands
     * should be made to this VkCommandbuffer instance.
     * @return The VkCommandBuffer instance for use by any following commands. 
    */
    VkCommandBuffer Begin();

    /**
     * @brief Ends the VkCommandBuffer.
    */
    const VkCommandBuffer& End();

    inline const VkCommandBuffer& GetCurrentCommandBuffer() const {return mCommandBuffer; }

private:
    /**
     * @brief Creates a single VkCommandBuffer instance.
    */
    void CreateCommandBufffer();

private:
    CommandPool& mCommandPool;
    LogicalDevice& mLogicalDevice;

    VkCommandBuffer mCommandBuffer;

    bool mIsRunning = false;

};
}

#endif