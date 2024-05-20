#pragma once
#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"
#include "System.hpp"
#include "Events/Bus.hpp"
#include "PlayerController.hpp"

namespace Super 
{
class Scene 
{
public:
    // @param width Width of the swapchain. 
    // @param height Height of the swapchain.
    Scene(EventBus& eventBus, uint32_t width, uint32_t height);
    
    ~Scene();

    void Update();

    // Getter for the entity manager (which has a getter for all the entiies).
    inline EntityManager& GetEntityManager() { return mEntityManager; }

    // Static getter for the camera.
    static inline const std::shared_ptr<OrthographicCamera>& GetCamera() { return mCamera; }

private:
    static std::shared_ptr<OrthographicCamera> mCamera;

    EntityManager mEntityManager = EntityManager();

    std::unique_ptr<PlayerController> mPlayerController{nullptr};

    std::vector<std::unique_ptr<System>> mSystems{};
};
}