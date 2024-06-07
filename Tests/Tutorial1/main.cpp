#include <iostream>
#include <Engine.hpp>
#include <Game.hpp>

int main(int argc, char** argv) 
{
    mt::EngineDesc engineDesc;
    engineDesc.windowName = "DemoGame";
    engineDesc.windowWidth = 800;
    engineDesc.windowHeight = 600;

    mt::Engine engine = mt::Engine(&engineDesc);

    std::unique_ptr<Game> game = std::make_unique<Game>(engine);
 
    engine.SetGame(std::move(game));
}

class Game : public mt::IGame 
{
public:
    Game(mt::Engine& engine, uint32_t windowWidth, uint32_t windowHeight) : mt::IGame(engine) 
    {
        Load(windowWidth, windowHeight);
    }

    virtual void Load(uint32_t width, uint32_t height) override 
    {
        mRes.LoadImage("BackgroundImage", "Resources/Textures/Background.png");
        mRes.LoadImage("BoxImage", "Resources/Textures/Box.png");
        mRes.LoadImage("PlatformImage", "Resources/Textures/Platform.png");
        mRes.LoadImage("PlayerImage", "Resources/Textures/Player.png");

        mRes.LoadShader("SimpleShader", "Resources/Shaders/simple.vert", "Resources/Shaders/simple.frag");

        mCamera = std::make_unique<mt::OrthographicCamera>(width, height, glm::vec3(0.0f, 0.0f, 5.0f));

        mt::TempRenderObj player{};
        player.color = glm::vec3(1.0f, 0.0f, 0.0f);
        player.posiiton = glm::vec2(200, 200);
        player.size = glm::vec2(50, 50);
        player.camera.projection = mCamera->GetProjectionMatrix();
        player.camera.view = mCamera->GetViewMatrix();
        player.textureName = "PlayerImage";

        glm::mat4 model{1.0f};
        model = glm::scale(model, glm::vec3(player.size, 1.0));
        model = glm::translate(model, glm::vec3(player.posiiton, 1.0));
        player.transform.transformMatrix = model;


    }

    virtual void Run(std::chrono::duration<double>& ts) override 
    {
        
    }

    virtual void Quit() override 
    {

    }

};

