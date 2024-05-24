#pragma once
#include <iostream>
#include "RenderSystem.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"

namespace Super 
{
class Renderer 
{
public:
    Renderer(Device& device, Window& window);
    ~Renderer();

    VkCommandBuffer GetCurrentCommandBuffer() const;
    void RecreateSwapChain();
    void CreateCommandBufffers();

    VkCommandBuffer Begin();
    void BeginRenderPass(VkCommandBuffer commandBuffer);
    void Render(VkCommandBuffer commandBuffer, std::vector<Entity>& entities);
    void EndRenderPass(VkCommandBuffer commandBuffer);
    void End();
    void FreeCommandBuffers();

    // Getters
    //
    inline const int& GetFrameIndex() const 
    {
        assert(mIsFrameStarted && "Cannot request frame index from renderer when the frame hasn't started!");
        return mCurrentFrameIndex;
    }


private:
    Device& mDevice;

    Window& mWindow;

    std::unique_ptr<SwapChain> mSwapChain = nullptr;
    
    std::vector<VkCommandBuffer> mCommandBuffers{};

    std::vector<RenderSystem*> mRenderSystems{};

    uint32_t mCurrentImageIndex = 0;
    int mCurrentFrameIndex = 0;
    bool mIsFrameStarted = false;

};
}