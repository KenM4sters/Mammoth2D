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

        std::unique_ptr<Entity>& player = Vulkan2D::CreateEntity();
        player.AddComponent<Transform>({300, 300}, {1.0, 1.0});
        player.AddComponent<RigidBody>();
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
