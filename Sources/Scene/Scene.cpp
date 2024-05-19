#include "Scene.hpp"
#include "PlayerController.hpp"
#include "Physics/Physics.hpp"
#include "Physics/Collision.hpp"

namespace Super 
{

std::shared_ptr<OrthographicCamera> Scene::mCamera = nullptr;

     
Scene::Scene(uint32_t width, uint32_t height) 
{
    CreateScene(width, height);
}

Scene::~Scene() 
{
}

void Scene::Update() 
{
    for(const auto& sys : mSystems) 
    {
        sys->Update(mEntityManager.GetAllEntities());
    }
}


void Scene::CreateScene(uint32_t width, uint32_t height) 
{
    mCamera = std::make_shared<OrthographicCamera>(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Player Entity.
    //
    Entity player = Entity{};
    player.color = glm::vec3(0.5f, 0.1f, 1.0f);
    player.transform = {glm::vec2(400, 100), glm::vec2(50, 50), glm::mat4{1.0f}};
    player.bounds.size = player.transform.scale;
    player.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    player.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::HAS_MOTION | EntityFlags::IS_PLAYER;
    player.id = mEntityManager.CreateEntity(std::move(player));

    // Enemy Entity.
    //
    Entity enemy = Entity{};
    enemy.color = glm::vec3(0.5f, 1.0f, 0.1f);
    enemy.transform = {glm::vec2(200, 100), glm::vec2(50, 50), glm::mat4{1.0f}};
    enemy.bounds.size = enemy.transform.scale;
    enemy.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    enemy.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::HAS_MOTION | EntityFlags::IS_ENEMY;
    enemy.id = mEntityManager.CreateEntity(std::move(enemy));

    // Event Systems.
    //

    mEventSystems.emplace_back(std::move(std::make_unique<PlayerController>(mEntityManager.GetAllEntities()[0])));


    // ECS Systems.
    //   
    mSystems.emplace_back(std::move(std::make_unique<Physics>()));
    mSystems.emplace_back(std::move(std::make_unique<Collision>(width, height)));
}
}