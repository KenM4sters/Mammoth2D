#ifndef MAMMOTH_2D_ENGINE_HPP
#define MAMMOTH_2D_ENGINE_HPP

#include "Window.hpp"
#include "Graphics/Graphics.hpp"
#include "Device.hpp"
#include "Input.hpp"
#include "Events/Bus.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"
#include <Delta/ECS.hpp>

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

    inline dt::ECS& GetECS() { return mECS; }

    inline ResourceManager& GetResourceManager() { return mResourceManager; }

    void SetGame(std::unique_ptr<IGame> game);

    void WaitDevice();

    void DrawTempObj(TempRenderObj& obj);

    /**
     * @brief function to tell the renderer to draw a simple quadrilateral.
     * @param size a 2d vector containing the width and height values of the desired quad.
     * @param position a 2d vector containing the x and y coordinates of the top-left corner of the desired quad.
     * @param color a 3d vector containing the RGB color values of the desired quad.
    */
    void DrawQuad(glm::vec2 size, glm::vec2 position, glm::vec3 color);

private:

    void Update();

private:
    EventBus mEventBus{};
    Window mWindow;
    Input mInput{&mEventBus, &mWindow};
    ResourceManager mResourceManager{};
    dt::ECS mECS;

    std::unique_ptr<Graphics> mGraphics = nullptr;

    std::unique_ptr<IGame> mGame = nullptr;
};
}

#endif