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

    

}

class Game : public mt::IGame 
{
public:
    Game(mt::Engine& engine)
        : mt::IGame(engine) {}

    virtual void Load() override 
    {
        mRes.LoadImage("BackgroundImage", "Resources/Textures/Background.png");
        mRes.LoadImage("BoxImage", "Resources/Textures/Box.png");
        mRes.LoadImage("PlatformImage", "Resources/Textures/Platform.png");
        mRes.LoadImage("PlayerImage", "Resources/Textures/Player.png");

        mRes.LoadShader("SimpleShader", "Resources/Shaders/simple.vert", "Resources/Shaders/simple.frag");


        
    }

    virtual void Run(std::chrono::duration<double>& ts) override 
    {
        
    }

    virtual void Quit() override 
    {

    }
};

