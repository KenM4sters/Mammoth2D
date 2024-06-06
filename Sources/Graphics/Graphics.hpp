#ifndef MAMMOTH_2D_GRAPHICS_HPP
#define MAMMOTH_2D_GRAPHICS_HPP

#include "Renderer/Renderer.hpp"
#include "Device.hpp"

#include <iostream>

namespace mt 
{
class Graphics  
{
public:
    Graphics(Window& window);
    ~Graphics();

    VkCommandBuffer GetCurrentCommandBuffer() const;
    void RecreateSwapChain();
    void CreateCommandBufffers();
    void FreeCommandBuffers();
    
    VkCommandBuffer Begin();
    void End();

    void PrepareGraphics(std::unique_ptr<IGame>& game);

    void Update();

    const std::unique_ptr<Renderer>& GetRenderer() const { return mRenderer; }
    const std::unique_ptr<Device>& GetDevice() const { return mDevice; }

    inline const int& GetFrameIndex() const;

private:
    Window& mWindow;

    std::unique_ptr<Renderer> mRenderer = nullptr;
    
    std::unique_ptr<SwapChain> mSwapChain = nullptr;

    std::unique_ptr<Device> mDevice = nullptr;

    std::vector<VkCommandBuffer> mCommandBuffers{};

    uint32_t mCurrentImageIndex = 0;
    int mCurrentFrameIndex = 0;
    bool mIsFrameStarted = false;


};

}

#endif