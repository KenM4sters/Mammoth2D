#pragma once
#include <iostream>
#include "RenderSystems/RenderSystem.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"

namespace Super 
{
class Renderer 
{
public:
    Renderer(std::shared_ptr<Device>& device, std::shared_ptr<Window>& window);
    ~Renderer();

    VkCommandBuffer GetCurrentCommandBuffer() const;
    void RecreateSwapChain();
    void CreateCommandBufffers();

    VkCommandBuffer Begin();
    void BeginRenderPass(VkCommandBuffer commandBuffer);
    void Render(VkCommandBuffer commandBuffer);
    void EndRenderPass(VkCommandBuffer commandBuffer);
    void End();
    void FreeCommandBuffers();


private:
    std::shared_ptr<Device> mDevice = nullptr;

    std::unique_ptr<SwapChain> mSwapChain = nullptr;

    std::shared_ptr<Window> mWindow = nullptr;
    
    std::vector<VkCommandBuffer> mCommandBuffers{};

    std::vector<RenderSystem*> mRenderSystems{};

    uint32_t mCurrentImageIndex = 0;
    int mCurrentFrameIndex = 0;
    bool mIsFrameStarted = false;

};
}