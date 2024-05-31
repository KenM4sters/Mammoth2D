#include "Engine.hpp"
#include <stdexcept>
#include <array>

namespace Super
{
Engine::Engine(EngineConfig* config)
    : mWindow{config->windowName, config->windowWidth, config->windowHeight}
{
    mRenderer = std::make_unique<Renderer>(mDevice, mWindow);
}

Engine::~Engine()
{
    
}

void Engine::Init()
{
    
}

void Engine::BeginDrawing()
{
    if(auto commandBuffer = mRenderer->Begin()) 
    {
        mRenderer->BeginRenderPass(commandBuffer);
    }
}

void Engine::EndDrawing() 
{
    if(auto commandBuffer = mRenderer->GetCurrentCommandBuffer()) 
    {
        mRenderer->EndRenderPass(commandBuffer);
        mRenderer->End();
    }
}

void Engine::Update() 
{
    glfwPollEvents();
    mInput.ListenToKeyboard(mWindow.GetNativeWindow());
}

void Engine::WaitDevice() 
{
    vkDeviceWaitIdle(mDevice.GetDevice());
} 
}