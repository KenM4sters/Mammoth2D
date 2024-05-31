#include <iostream>
#include <Engine.hpp>

int main(int argc, char** argv) 
{

    Super::EngineConfig config;
    config.windowName = "DemoGame";
    config.windowWidth = 800;
    config.windowHeight = 600;

    Super::Engine engine = Super::Engine(&config);


    while(engine.GetWindow().IsRunning()) 
    {
        engine.Update();
        engine.BeginDrawing();

        

        engine.EndDrawing();
    }
    engine.WaitDevice();

}