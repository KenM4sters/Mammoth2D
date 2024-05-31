#pragma once
#include <vector>
#include "Window.hpp"
#include "Graphics/Pipelines/Pipeline.hpp"
#include "Device.hpp"
#include "Graphics/Renderer/SwapChain.hpp"
#include "Graphics/Renderer/Renderer.hpp"
#include "Scene/Scene.hpp"
#include "Input.hpp"
#include "Events/Bus.hpp"

namespace Super
{
class Engine 
{
public:
    Engine(EngineConfig* config);
    ~Engine();

    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine& other) = delete;

    const Window& GetWindow() const { return mWindow; }

    void Init();

    void BeginDrawing();

    void EndDrawing();

    void Update();

    void WaitDevice();

private:
    EventBus mEventBus{};
    Window mWindow;
    Device mDevice{mWindow};

    std::unique_ptr<Renderer> mRenderer = nullptr;

    Input mInput{&mEventBus, &mWindow};

};
}