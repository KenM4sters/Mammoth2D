#ifndef MAMMOTH_2D_ENGINE_HPP
#define MAMMOTH_2D_ENGINE_HPP

#include "Window.hpp"
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Device.hpp"
#include "Graphics/Renderer/SwapChain.hpp"
#include "Graphics/Renderer/Renderer.hpp"
#include "Input.hpp"
#include "Events/Bus.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"

#include <vector>

namespace mt
{
struct EngineDesc 
{
    uint32_t windowWidth;
    uint32_t windowHeight;
    const char* windowName;
};

class Engine 
{
public:
    Engine(EngineDesc* config);
    ~Engine();

    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine& other) = delete;

    inline const Window& GetWindow() const { return mWindow; }

    inline const std::unique_ptr<Renderer>& GetRenderer() const { return mRenderer; } 

    inline ResourceManager& GetResourceManager() { return mResourceManager; }

    void SetGame(std::unique_ptr<IGame>& game);

    void BeginDrawing();

    void EndDrawing();

    void Update();

    void WaitDevice();

private:
    EventBus mEventBus{};
    Window mWindow;
    Device mDevice{mWindow};
    Input mInput{&mEventBus, &mWindow};
    ResourceManager mResourceManager{};

    std::unique_ptr<Renderer> mRenderer = nullptr;

    std::unique_ptr<IGame> mGame = nullptr;


};
}

#endif