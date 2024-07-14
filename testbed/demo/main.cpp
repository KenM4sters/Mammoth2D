
#include <mammoth/mamoth.hpp>
#include "window/window.hpp"

#include <iostream>

int main(const int argc, const char* const* const argv) 
{
    mt::GraphicsSettings settings;
    settings.backend = mt::GraphicsBackend::OpenGL;
    settings.name = "mammoth";
    settings.pixelViewportHeight = 600;
    settings.pixelViewportWidth = 800;

    mt::init(settings);

    mt::Program* program = mt::createProgram("testbed/resources/shaders/simple.vert", "testbed/resources/shaders/simple.frag");

    mt::Window* window = mt::getWindow();

    while(!window->shouldClose()) 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.0f, 0.2f, 1.0f);
        window->run();
    }

    program->destroy();
    delete program;
    
    mt::shutdown();
}

