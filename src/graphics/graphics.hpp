#include "Core.hpp"
#include "Factory.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

#include <iostream>

class Graphics final : public NonCopyable
{   
public:
    Graphics(IWindow& window, GraphicsAPI graphicsApi);

    ~Graphics();

    void Update();

    void Resize(const uint32_t width, const uint32_t height);

private:
    IWindow& mWindow;

    std::unique_ptr<IGraphicsFactory> mFactory = nullptr;

    std::unique_ptr<IRenderer> mRenderer = nullptr;
};