#ifndef MAMMOTH_2D_GRAPHICS_HPP
#define MAMMOTH_2D_GRAPHICS_HPP

#include "Graphics/Renderer/Renderer.hpp"
#include "Graphics/Devices/LogicalDevice.hpp"
#include "Graphics/Devices/Instance.hpp"
#include "Graphics/Devices/PhysicalDevice.hpp"
#include "Graphics/Commands/CommandBuffer.hpp"
#include "Graphics/Commands/CommandPool.hpp"

#include <iostream>

namespace mt 
{
class Graphics  
{
public:
    Graphics(Window& window);
    ~Graphics() {}

    const std::unique_ptr<Renderer>& GetRenderer() const { return mRenderer; }
    
    void RecreateSwapChain();
    
    VkCommandBuffer Begin();

    void End();

    void PrepareGraphics(IGame& game);

    void Update();

    inline const PhysicalDevice& GetPhysicalDevice() const { return *mPhysicalDevice; }
    inline const LogicalDevice& GetLogicalDevice() const { return *mLogicalDevice; }
    inline const Instance& GetInstance() const { return *mInstance; }

private:
    Window& mWindow;

    std::unique_ptr<Renderer> mRenderer = nullptr;
    
    std::unique_ptr<SwapChain> mSwapChain = nullptr;

    std::unique_ptr<LogicalDevice> mLogicalDevice = nullptr;
    std::unique_ptr<PhysicalDevice> mPhysicalDevice = nullptr;
    std::unique_ptr<Instance> mInstance = nullptr;
    std::unique_ptr<CommandPool> mCommandPool = nullptr;

    std::vector<std::unique_ptr<CommandBuffer>> mCommandBuffers{};

    uint32_t mCurrentImageIndex = 0;
    int mCurrentFrameIndex = 0;  
    bool mHasFrameStarted = false;  
};

}

#endif