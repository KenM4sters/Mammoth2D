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
class Program 
{
public:
    Program(uint32_t width, uint32_t height, const char* name);
    ~Program();

    Program(const Program& other) = delete;
    Program& operator=(const Program& other) = delete;

    void Init();

    void Run();

private:

    EventBus mEventBus{};

    Window mWindow;
    Device mDevice{mWindow};

    std::unique_ptr<Renderer> mRenderer = nullptr;
    std::unique_ptr<Scene> mScene = nullptr;

    Input mInput{mEventBus};

};
}