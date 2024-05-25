#include "Scene.hpp"
#include "Physics/Physics.hpp"
#include "Physics/Collision.hpp"
#include "Logging.hpp"

namespace Super 
{

std::shared_ptr<OrthographicCamera> Scene::mCamera = nullptr;

     
Scene::Scene(EventBus& eventBus, uint32_t width, uint32_t height) 
{
    mCamera = std::make_shared<OrthographicCamera>(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Player Entity.
    //
    Entity player = Entity{};
    player.flags = EntityFlags::ACTIVE | EntityFlags::IS_RIGID | EntityFlags::PLAYER_CONTROLLED;

    player.tx = {glm::vec2(350, 100), glm::vec2(50, 50)};
    player.body.inverseMass = 0.1f;
    player.body.force = {0.0f, 0.0f};
    player.body.velocity = {0.0f, 0.0f};
    player.body.staticFrictionCoefficient = 0.1f;
    player.body.dynamicFrictionCoefficient = 0.3f;
    player.body.restitution = 0.0f;

    player.color = glm::vec3(0.3f, 0.3f, 1.0f);
    player.label = "Player";
    mEntityManager.CreateEntity(std::move(player));

    // Enemy Entity.
    //
    Entity box = Entity{};
    box.flags = EntityFlags::ACTIVE | EntityFlags::IS_RIGID;
    
    box.tx = {glm::vec2(250, 100), glm::vec2(50, 50)};
    box.body.inverseMass = 0.1f;
    box.body.force = {0.0f, 0.0f};
    box.body.velocity = {0.0f, 0.0f};
    box.body.staticFrictionCoefficient = 0.1f;
    box.body.dynamicFrictionCoefficient = 0.3f;
    box.body.restitution = 0.0f;

    box.color = glm::vec3(1.0f, 0.3f, 0.3f);
    box.label = "Box";
    mEntityManager.CreateEntity(std::move(box));

    // Platform 1 Entity.
    //
    Entity platform = Entity{};
    platform.flags = EntityFlags::ACTIVE | EntityFlags::IS_RIGID;
    
    platform.tx = {glm::vec2(100, 500), glm::vec2(600, 20)};
    box.body.inverseMass = 0.0f;
    platform.body.force = {0.0f, 0.0f};
    platform.body.velocity = {0.0f, 0.0f};
    platform.body.staticFrictionCoefficient = 0.1f;
    platform.body.dynamicFrictionCoefficient = 0.3f;
    platform.body.restitution = 0.0f;


    platform.color = glm::vec3(0.5f, 0.2f, 0.8f);
    platform.label = "Platform";
    mEntityManager.CreateEntity(std::move(platform));

    // Background Entity.
    //
    Entity background = Entity{};
    background.flags = EntityFlags::ACTIVE;

    background.tx = {glm::vec2(0, 0), glm::vec2(800, 600)};
    background.body.inverseMass = 0.0f;
    background.body.force = {0.0f, 0.0f};
    background.body.velocity = {0.0f, 0.0f};
    background.body.staticFrictionCoefficient = 0.1f;
    background.body.dynamicFrictionCoefficient = 0.3f;
    background.body.restitution = 0.0f;


    background.color = glm::vec3(0.3f, 0.3f, 1.0f);
    background.label = "Background";
    mEntityManager.CreateEntity(std::move(background));

    // Event-Specific callback classes.
    // These classes don't have any functions that are called each frame, but rather
    // provide callbacks for the EventBus, so they just exist and remain idle for the 
    // entire application (until the program closes).
    //
    mPlayerController = std::make_unique<PlayerController>(eventBus, mEntityManager.GetAllEntities()[0]);




    // ECS Systems.
    // Unlike event callbacks, these systems are run each frame and have more of a profound
    // impact on the application, though they may still publish and subscribe to events.
    //   
    mSystems.emplace_back(std::move(std::make_unique<Physics>(eventBus)));
    mSystems.emplace_back(std::move(std::make_unique<Collision>(eventBus, width, height)));
}

Scene::~Scene() 
{
    // Doesn't need to manually free any memory... empty for now.
}

void Scene::Update() 
{
    for(const auto& sys : mSystems) 
    {
        sys->Update(mEntityManager.GetAllEntities());
    }
}


}