#ifndef MAMMOTH_2D_GAME_HPP
#define MAMMOTH_2D_GAME_HPP

#include "Camera.hpp"

namespace mt 
{

class Engine;

enum Shapes 
{
    Quad = 0,
    Triangle = 1,
    Circle = 2
};

struct TempRenderObj 
{
    glm::vec2 posiiton{200, 200};
    glm::vec2 size{200, 200};
    glm::vec3 color{1.0, 0.5, 0.0};
    glm::mat4 projection{1.0f};
    glm::mat4 view{1.0f};
    std::string textureName = "";
};

class IGame 
{
public:
    IGame(Engine& engine) : m2d{engine}, mRes{engine.GetResourceManager()} 
    {
    }

    virtual void Load(uint32_t width, uint32_t height) = 0;
    
    virtual void Run(std::chrono::duration<double>& ts) = 0;

    virtual void Quit() = 0;

    virtual void PreRender() {};

    virtual void PostRender() {};

    inline const std::unique_ptr<mt::OrthographicCamera>& GetCamera() const { return mCamera; }
    inline const mt::TempRenderObj& GetObj() const { return mObj; }

protected:
    Engine& m2d;
    ResourceManager& mRes;
    mt::TempRenderObj mObj;
    std::unique_ptr<mt::OrthographicCamera> mCamera = nullptr;
};
}

#endif