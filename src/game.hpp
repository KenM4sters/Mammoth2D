#ifndef MAMMOTH_2D_GAME_HPP
#define MAMMOTH_2D_GAME_HPP

#include "Camera.hpp"
#include "Engine.hpp"

namespace mt 
{

enum Shapes 
{
    Quad = 0,
    Triangle = 1,
    Circle = 2
};

struct TransformComp 
{
    glm::mat4 transformMatrix;
    VkDescriptorSet descriptorSet = nullptr;
    VkWriteDescriptorSet writer{};
};

struct CameraComp 
{
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};
    VkDescriptorSet descriptorSet = nullptr;
    VkWriteDescriptorSet writer{};
};

struct MaterialComp 
{
    std::string texture = "";
    VkDescriptorSet descriptorSet = nullptr;
    VkWriteDescriptorSet writer{};
};

struct TempRenderObj 
{
    std::unique_ptr<CameraComp> camera = nullptr;
    std::unique_ptr<TransformComp> transform = nullptr;
    std::unique_ptr<MaterialComp> material = nullptr;
    glm::vec2 posiiton{200, 200};
    glm::vec2 size{200, 200};
    glm::vec3 color{1.0, 0.5, 0.0};
    std::string shaderFile = "";
};


/**
 * @brief The base Game class that user-defined games need to inherit from. 
 * This is a WIP.
*/
class IGame 
{
public:
    IGame(Engine& engine) : m2d{engine}, mRes{engine.GetResourceManager()} 
    {
    }

    /**
     * @brief This is where all of the game-specific elements need to be initialized.
     * Think Cameras, Entties, Resources etc...
     * @param width the width of the window that's needed for the aspect ratio of the camera.
     * @param height the height of the window that's needed for the aspect ratio of the camera.
    */
    virtual void Load(uint32_t width, uint32_t height) = 0;

    /**
     * @brief Typically the only calls you'll need to make here is to run each of the ECS 
     * systems which would need the time step between frames to move elements consistently
     * across devices (under different frame rates).
     * @param ts the time step, otherwise known as delta time. 
    */
    virtual void Run(std::chrono::duration<double>& ts) = 0;

    /**
     * @brief Deallocates all resources.
    */
    virtual void Quit() = 0;

    /**
     * @brief TODO.
    */
    virtual void PreRender() {};

    /**
     * @brief TODO.
    */
    virtual void PostRender() {};

    inline const std::unique_ptr<mt::OrthographicCamera>& GetCamera() const { return mCamera; }
    inline const std::vector<mt::TempRenderObj>& GetObj() const { return mObj; }

protected:
    Engine& m2d;
    ResourceManager& mRes;

    std::vector<mt::TempRenderObj> mObj{};

    std::unique_ptr<mt::OrthographicCamera> mCamera = nullptr;
};
}

#endif