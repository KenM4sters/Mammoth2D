## Thesis

The following code snippet demonstrates how I think a game using the Vulkan2D engine
should interact with the engine in order to acheive a good balance of simplicity and flexibility. 

This is a work in progress.

```
int main(int argc, char** argv) 
{
    EngineConfig config;
    config.windowName = "DemoGame";
    config.windowWidth = 800;
    config.windowHeight = 600;

    Engine engine = Engine(&config);

    Game game;

    engine.OpenGame(&game);
}

class Game : public Engine::Game 
{
public:
    Game(std::unique_ptr<Engine>& engine) : Vulkan2D(engine) {}
    ~Game() {}

    void Load() override 
    {
        Vulkan2D.ResourceManager.LoadResource<Image>("playerTexture", "XXX.png");
        Vulkan2D.ResourceManager.LoadResource<Image>("enemy1Texture", "XXX.png");
        Vulkan2D.ResourceManager.LoadResource<Shader>("basicShader", "XXX.vert", "XXX.frag");

        Vulkan2D::GameObject player{};
        player.geometry = Vulkan2D::Geometry(Vulkan2D::GeometryTypes.Square);
        player.geometry.position = {300, 300};
        player.material = Vulkan2D::BasicMaterial(Vulkan2D::Colors.Red);
        player.material.AddTexture(Vulkan2D.ResourceManager.GetImage("playerTexture));
        Vulkan2D.Physics.AddCollisionBody(&player, Physics::CollisionShapes.AABB);
        SubmitGameObject(player);
        
        Vulkan2D::GameObject enemy1{};
        enemy1.geometry = Vulkan2D::Geometry(Vulkan2D::GeometryTypes.Square);
        enemy1.geometry.position = {100, 100};
        enemy1.material = Vulkan2D::BasicMaterial(Vulkan2D::Colors.Blue);
        enemy1.material.AddTexture(Vulkan2D.ResourceManager.GetImage("enemy1Texture));
        Vulkan2D.Physics.AddCollisionBody(&enemy1, Physics::CollisionShapes.AABB);
        SubmitGameObject(enemy1);
    }

    void Run() override
    {
        while(this->IsRunning()) 
        {
            /*
            * Calculate delta time
            */
            Vulkan2D.UpdateGameObjects(mGameObjects, dt);
            Vulkan2D.Renderer::Render(mGameObjects);
        }
    }

    void Quit() override 
    {
        Vulkan2D.QuitGame(this);
    } 
}
```
