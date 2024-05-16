#include "Program.hpp"
#include <stdexcept>
#include <array>

namespace Super
{
Program::Program(uint32_t width, uint32_t height, const char* name)
{

    mWindow = std::make_shared<Window>(name, width, height);
    
    mDevice = std::make_shared<Device>(mWindow);
 
    mSwapChain = std::make_unique<SwapChain>(mDevice, mWindow->GetExtent());

    CreatePipelineLayout();
    CreatePipeline();
    CreateCommandBuffers();
}

Program::~Program()
{
    vkDestroyPipelineLayout(mDevice->GetDevice(), mPipelineLayout, nullptr);
}

void Program::Init()
{
    
}

void Program::CreatePipelineLayout() 
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pPushConstantRanges = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    
    if(vkCreatePipelineLayout(mDevice->GetDevice(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void Program::CreatePipeline() 
{
    Pipeline_Desc pipelineConfig = Pipeline::DefaultPipelineDesc(mSwapChain->GetWidth(), mSwapChain->GetHeight());

    pipelineConfig.renderPass = mSwapChain->GetRenderPass();

    pipelineConfig.pipelineLayout = mPipelineLayout;

        mPipeline = std::make_unique<Pipeline>(
        mDevice, 
        std::move(pipelineConfig),
        "Shaders/simple.vert.spv", 
        "Shaders/simple.frag.spv"
    );

}

void Program::CreateCommandBuffers() 
{
    mCommandBuffers.resize(mSwapChain->GetImageCount());

    VkCommandBufferAllocateInfo allocInfo{};

    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice->GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

    if(vkAllocateCommandBuffers(mDevice->GetDevice(), &allocInfo, mCommandBuffers.data()) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to allocate command buffers");
    }

    for(int i = 0; i < mCommandBuffers.size(); i++) 
    {
        VkCommandBufferBeginInfo beginInfo{};   
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(mCommandBuffers[i], &beginInfo) != VK_SUCCESS) 
        {
            throw std::runtime_error("Failed to begin recording the command buffers!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = mSwapChain->GetRenderPass();
        renderPassInfo.framebuffer = mSwapChain->GetFrameBuffer(i);
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = mSwapChain->GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.0f, 0.5f, 1.0f};
        clearValues[1].depthStencil = {1.0f, (uint32_t)0}; // Expects a float for the depth and a uint32_t for the stencil.
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(mCommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        mPipeline->Bind(mCommandBuffers[i]);

        vkCmdDraw(mCommandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(mCommandBuffers[i]);

        if(vkEndCommandBuffer(mCommandBuffers[i]) != VK_SUCCESS) 
        {
            throw std::runtime_error("Failed to end command buffers!");
        }
    }
}

void Program::DrawFrame() 
{
    uint32_t imageIndex;
    auto result = mSwapChain->AcquireNextImage(&imageIndex);

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
    {
        throw std::runtime_error("Failed to acquire next image!");
    }

    result = mSwapChain->SubmitCommandBuffers(&mCommandBuffers[imageIndex], &imageIndex);

    if(result != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to present swap chain image!");
    }
}



void Program::Run()
{
    while(Window::IsRunning()) 
    {
        glfwPollEvents();
        DrawFrame();
    }

    vkDeviceWaitIdle(mDevice->GetDevice());
}
}