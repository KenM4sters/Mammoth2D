#pragma once
#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"

namespace Super 
{
class Scene 
{
public:
    // @param width Width of the swapchain. 
    // @param height Height of the swapchain.
    Scene(uint32_t width, uint32_t height);
    
    ~Scene();

    void CreateScene(uint32_t width, uint32_t height);

    // Getter for the entity manager (which has a getter for all the entiies).
    inline EntityManager& GetEntityManager() { return mEntityManager; }

    // Static getter for the camera.
    static inline const std::shared_ptr<OrthographicCamera>& GetCamera() { return mCamera; }

private:
    static std::shared_ptr<OrthographicCamera> mCamera;

    EntityManager mEntityManager = EntityManager();
};
}