#include "Scene.hpp"
#include "Physics/Physics.hpp"
#include "Physics/Collision.hpp"

namespace Super 
{

std::shared_ptr<OrthographicCamera> Scene::mCamera = nullptr;

     
Scene::Scene(EventBus& eventBus, uint32_t width, uint32_t height) 
{
    mCamera = std::make_shared<OrthographicCamera>(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Player Entity.
    //
    Entity player = Entity{};
    player.color = glm::vec3(0.5f, 0.1f, 1.0f);
    player.transform = {glm::vec2(450, 200), glm::vec2(50, 50), glm::mat4{1.0f}};
    player.bounds.size = player.transform.scale;
    player.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    player.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::HAS_MOTION | EntityFlags::IS_PLAYER;
    player.id = mEntityManager.CreateEntity(std::move(player));

    // Enemy Entity.
    //
    Entity enemy = Entity{};
    enemy.color = glm::vec3(0.5f, 1.0f, 0.1f);
    enemy.transform = {glm::vec2(250, 200), glm::vec2(50, 50), glm::mat4{1.0f}};
    enemy.bounds.size = enemy.transform.scale;
    enemy.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    enemy.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::HAS_MOTION | EntityFlags::IS_ENEMY;
    enemy.id = mEntityManager.CreateEntity(std::move(enemy));

    // Platform 1 Entity.
    //
    Entity platform1 = Entity{};
    platform1.color = glm::vec3(1.0f, 1.0f, 0.0f);
    platform1.transform = {glm::vec2(200, 400), glm::vec2(400, 15), glm::mat4{1.0f}};
    platform1.bounds.size = platform1.transform.scale;
    platform1.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    platform1.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::IS_PLATFORM;
    platform1.id = mEntityManager.CreateEntity(std::move(platform1));

    // Platform 2 Entity.
    //
    Entity platform2 = Entity{};
    platform2.color = glm::vec3(1.0f, 1.0f, 0.0f);
    platform2.transform = {glm::vec2(600, 200), glm::vec2(100, 15), glm::mat4{1.0f}};
    platform2.bounds.size = platform2.transform.scale;
    platform2.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    platform2.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::IS_PLATFORM;
    platform2.id = mEntityManager.CreateEntity(std::move(platform2));

    // Platform 3 Entity.
    //
    Entity platform3 = Entity{};
    platform3.color = glm::vec3(1.0f, 1.0f, 0.0f);
    platform3.transform = {glm::vec2(100, 200), glm::vec2(100, 15), glm::mat4{1.0f}};
    platform3.bounds.size = platform3.transform.scale;
    platform3.motion = {glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f)};
    platform3.flags = EntityFlags::ACTIVE | EntityFlags::HAS_HEALTH | EntityFlags::IS_RIGID 
    | EntityFlags::IS_PLATFORM;
    platform3.id = mEntityManager.CreateEntity(std::move(platform3));


    // Event Systems.
    //

    mPlayerController = std::make_unique<PlayerController>(eventBus, mEntityManager.GetAllEntities()[0]);


    // ECS Systems.
    //   
    mSystems.emplace_back(std::move(std::make_unique<Physics>()));
    mSystems.emplace_back(std::move(std::make_unique<Collision>(width, height)));
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


}