#include "Program.hpp"
#include <stdexcept>
#include <array>

namespace Super
{
Program::Program(uint32_t width, uint32_t height, const char* name)
    : mWindow{name, width, height}
{
    mRenderer = std::make_unique<Renderer>(mDevice, mWindow);

    mScene = std::make_unique<Scene>(width, height);
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
        mInput.ListenToKeyboard(mWindow.GetNativeWindow());
        if(auto commandBuffer = mRenderer->Begin()) 
        {
            mRenderer->BeginRenderPass(commandBuffer);
            mRenderer->Render(commandBuffer, mScene->GetEntityManager().GetAllEntities());
            mRenderer->EndRenderPass(commandBuffer);
            mRenderer->End();
        }
        
        mScene->Update();
    }

    vkDeviceWaitIdle(mDevice.GetDevice());
}
}