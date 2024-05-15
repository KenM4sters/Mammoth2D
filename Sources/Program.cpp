#include "Program.hpp"

namespace Super
{
Program::Program(uint32_t width, uint32_t height, const char* name)
{

    mWindow = std::make_shared<Window>(name, width, height);
    
    mDevice = std::make_shared<Device>(mWindow);

    mPipeline = std::make_unique<Pipeline>(
        mDevice, 
        Pipeline::DefaultPipelineDesc(width, height),
        "Shaders/simple.vert.spv", 
        "Shaders/simple.frag.spv"
    );
}

Program::~Program()
{

}

void Program::Init()
{
    
}

void Program::Run()
{
    while(Window::IsRunning()) 
    {
        glfwPollEvents();
    }
}
}