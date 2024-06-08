#ifndef MAMMOTH_2D_COMMAND_POOL_HPP
#define MAMMOTH_2D_COMMAND_POOL_HPP


#include "Graphics/Devices/LogicalDevice.hpp"

namespace mt 
{

/**
 * @brief Wrapper for a VkCommandPool (the only one in our case) which is required by a
 * VkCommandBuffer.
*/
class CommandPool 
{
public:
    /**
     * @brief Constructs an instance of a CommandPool. The logical device reference is stored
     * so that this class can properly free the CommandPool when our engine stops running.
     * @param physicalDevice a PhysicalDevice instance.
     * @param logicalDevice a LogicalDevice instance.
    */
    CommandPool(PhysicalDevice& physicalDevice, LogicalDevice& logicalDevice);
    ~CommandPool();

    inline const VkCommandPool& GetCommandPool() const { return mCommandPool; }

private:
    /**
     * @brief Creates a CommandPool.
     * @param physicalDevice a PhysicalDevice instance (no need to store this).
    */
    void CreateCommandPool(PhysicalDevice& physicalDevice);

private:
    LogicalDevice& mLogicalDevice;
    VkCommandPool mCommandPool;
};

}

#endif