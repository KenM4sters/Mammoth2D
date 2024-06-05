#include "Engine.hpp"

#include <chrono>
#include <stdexcept>
#include <array>

namespace mt
{

Engine::Engine(EngineDesc* config)
    : mWindow{config->windowName, config->windowWidth, config->windowHeight}
{
    mRenderer = std::make_unique<Renderer>(mDevice, mWindow);
}

Engine::~Engine()
{
    
}

void Engine::SetGame(std::unique_ptr<IGame>& game) 
{
    mGame = std::move(game);
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
    mWindow.ListenToEvents();
    mInput.ListenToKeyboard(mWindow.GetNativeWindow());

    auto previousFrame = std::chrono::high_resolution_clock::now();

    while(mWindow.IsRunning()) 
    {
        auto currentFrame = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> ts = currentFrame - previousFrame;

        BeginDrawing();

        mGame->Run(ts);

        EndDrawing();
    }
    WaitDevice();
}

void Engine::WaitDevice() 
{
    vkDeviceWaitIdle(mDevice.GetDevice());
} 
}