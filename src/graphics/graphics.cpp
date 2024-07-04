#include "Graphics.hpp"


Graphics::Graphics(IWindow& window, GraphicsAPI graphicsApi)
    : mWindow{window}
{
    switch(graphicsApi) 
    {
        case GraphicsAPI::OpenGL: mRenderer = std::make_unique<OpenGLRenderer>(); break;
        case GraphicsAPI::Vulkan: mRenderer = std::make_unique<VulkanRenderer>(); break;
    }
}

Graphics::~Graphics() 
{
    
}

void Graphics::Update() 
{
    
}

void Graphics::Resize(const uint32_t width, const uint32_t height) 
{
    
}