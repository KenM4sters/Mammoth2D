#include "Scene.hpp"

namespace Super 
{
     
Scene::Scene(uint32_t width, uint32_t height) 
{
    CreateScene(width, height);
}

Scene::~Scene() 
{
}


void Scene::CreateScene(uint32_t width, uint32_t height) 
{
    mCamera = std::make_shared<OrthographicCamera>(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Initial player props.
    //
    mPlayer = Entity{};
    mPlayer.id = EntityManager::CreateEntity(&mPlayer);
    mPlayer.color = glm::vec3(0.5f, 0.1f, 1.0f);
    mPlayer.transform = {glm::vec2(400, 400), glm::vec2(50, 50), glm::mat3{1.0f}};
    mPlayer.physics = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    mPlayer.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
                    | EntityFlags::HAS_MOTION | EntityFlags::PLAYER_CONTROLLED;
}
}