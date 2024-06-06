#include "Engine.hpp"

#include <chrono>
#include <stdexcept>
#include <array>

namespace mt
{

Engine::Engine(EngineDesc* config)
    : mWindow{config->windowName, config->windowWidth, config->windowHeight}
{
    mGraphics = std::make_unique<Graphics>(mWindow);
}

Engine::~Engine()
{
    
}

void Engine::SetGame(std::unique_ptr<IGame> game) 
{
    mGame = std::move(game);
    mGraphics->PrepareGraphics(game);
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

        // Purely game logic being updated here - no rendering of sorts.
        mGame->Run(ts);

        // Renders all Entities. 
        mGraphics->Update();
    }

    WaitDevice();
}

void Engine::WaitDevice() 
{
    vkDeviceWaitIdle(mGraphics->GetDevice()->GetDevice());
}

void Engine::DrawQuad(glm::vec2 size, glm::vec2 position, glm::vec3 color) 
{
    
}

void Engine::DrawTempObj(TempRenderObj& obj) 
{
    mGraphics->GetRenderer()->DrawTempObj(obj);
}
}