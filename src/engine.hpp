#ifndef MAMMOTH_2D_ENGINE_HPP
#define MAMMOTH_2D_ENGINE_HPP

#include "Window.hpp"
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


/**
 * @brief Entry point for the game engine - typically the only engine-specific class that 
 * you would interact with. This class contains member functions that forward commands to member
 * classes (Graphics, Input etc...).
*/
class Engine 
{
public:
    /**
     * @brief Constructs the Engine with an EngineDesc instance.
     * @param desc A description of the customizable engine features that's used to
     * construct the engine itself. This is required and no overload exists to bypass this. 
    */
    Engine(EngineDesc* desc);
    ~Engine();

    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine& other) = delete;

    /**
     * @brief Sets the Game member variable and begins creating the graphics pipeline with this 
     * game. This must be called once the user has created their own game and now wishes to play it.
     * @param game an r-value reference to the game. Beware that the game will no longer be accessible 
     * to the user and the engine takes full ownership. 
    */
    void SetGame(std::unique_ptr<IGame>&& game);

    inline const Window& GetWindow() const { return mWindow; }
    inline dt::ECS& GetECS() { return mECS; }
    inline ResourceManager& GetResourceManager() { return mResourceManager; }

private:
    /**
     * @brief Begins the render loop and coordinates any runtime functions
     * (event listeners, draw commands etc...).
     * Please note that only a porton of the body of this function is within the render loop.  
    */
    void Update();

    /**
     * @brief Blocks all commands to the logical device until the current commands have been
     * processed in full. This is required before any cleanup calls are made, since attempting
     * to free a resource while it's still in use could lead to a nullptr dereference (crash).
     * Since we're responsible for managing this synchronization, we make a call to this function
     * once the game loop has terminated, but before any stack allocated resources have been released.
    */
    void WaitDevice();

private:
    EventBus mEventBus{};
    ResourceManager mResourceManager{};

    Window mWindow;
    Input mInput{&mEventBus, &mWindow};
    
    dt::ECS mECS;

    std::unique_ptr<Graphics> mGraphics = nullptr;
    
    std::unique_ptr<IGame> mGame = nullptr;
};
}

#endif