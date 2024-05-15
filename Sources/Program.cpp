#include "Program.hpp"

namespace Super
{
Program::Program(uint32_t width, uint32_t height, const char* name)
{
    mWindow = std::make_unique<Window>(name, width, height);
}

Program::~Program()
{

}

void Program::Init()
{
    mWindow->Init();
}

void Program::Run()
{
    while(Window::IsRunning()) 
    {
        glfwPollEvents();
    }
}
}