#include "Program.hpp"
#include <stdexcept>
#include <array>

namespace Super
{
Program::Program(uint32_t width, uint32_t height, const char* name)
{

    mWindow = std::make_shared<Window>(name, width, height);
    
    mDevice = std::make_shared<Device>(mWindow);

    mRenderer = std::make_unique<Renderer>(mDevice, mWindow);

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
        if(auto commandBuffer = mRenderer->Begin()) 
        {
            mRenderer->BeginRenderPass(commandBuffer);
            mRenderer->Render(commandBuffer);
            mRenderer->EndRenderPass(commandBuffer);
            mRenderer->End();
        }
    }

    vkDeviceWaitIdle(mDevice->GetDevice());
}
}