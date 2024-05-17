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

    // Getters
    //
    inline const Entity& GetPlayer() const { return mPlayer; }
    inline const std::shared_ptr<OrthographicCamera>& GetCamera() const { return mCamera; }
    inline const std::vector<Entity>& GetEnemies() const { return mEnemies; }
    inline const std::vector<Entity>& GetBullets() const { return mBullets; }
    inline const std::vector<Entity>& GetPlatforms() const { return mPlatforms; }


private:
    std::shared_ptr<OrthographicCamera> mCamera = nullptr;
    Entity mPlayer;
    std::vector<Entity> mEnemies{};
    std::vector<Entity> mBullets{};
    std::vector<Entity> mPlatforms{};
};
}