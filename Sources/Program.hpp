#pragma once
#include <vector>
#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"

namespace Super
{
class Program 
{
public:
    Program(uint32_t width, uint32_t height, const char* name);
    ~Program();

    Program(const Program& other) = delete;
    Program& operator=(const Program& other) = delete;

    void Init();

    void Run();

    void CreatePipelineLayout();
    void CreatePipeline();
    void CreateCommandBuffers();
    void DrawFrame();

private:

    std::shared_ptr<Window> mWindow = nullptr;

    std::shared_ptr<Device> mDevice = nullptr;

    std::unique_ptr<Pipeline> mPipeline = nullptr;

    std::unique_ptr<SwapChain> mSwapChain = nullptr;

    VkPipelineLayout mPipelineLayout;
    
    std::vector<VkCommandBuffer> mCommandBuffers;

};
}