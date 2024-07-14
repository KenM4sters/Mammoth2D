
#include <mammoth/mamoth.hpp>
#include "window/window.hpp" 

#include <iostream>

static float vertices[] = 
{
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f
};

static int indices[] = 
{
    0, 1, 2, 0, 3, 2
};

int main(const int argc, const char* const* const argv) 
{
    mt::GraphicsSettings settings;
    settings.backend = mt::GraphicsBackend::OpenGL;
    settings.name = "mammoth";
    settings.pixelViewportHeight = 600;
    settings.pixelViewportWidth = 800;

    mt::init(settings);

    mt::ProgramHandle program = mt::createProgram("testbed/resources/shaders/test.vert", "testbed/resources/shaders/test.frag");

    uint32_t vFlags;
    mt::Memory vMem = {(void*)vertices, 32};
    mt::VertexBufferHandle vertexBuffer = mt::createVertexBuffer(&vMem, vFlags);

    uint32_t fFlags;
    mt::Memory fMem = {(void*)indices, 24};
    mt::IndexBufferHandle indexBuffer = mt::createIndexBuffer(&fMem, fFlags);

    mt::VertexAttribute attributes[1] = 
    {
        {mt::Attribute::Position, mt::ValueType::Float, 2}
    }; 

    mt::VertexLayout vLayout = {attributes, 1};

    mt::VertexInputHandle vInput = mt::createVertexInput(vertexBuffer.get(), &vLayout, indexBuffer.get());





    int test = 10;
    mt::Memory uTestMem = {(void*)&test, 4};
    mt::ResourceHandle uTest = mt::createResource("uTest", mt::ResourceType::Int, &uTestMem);

    mt::ShaderHandle shader = mt::createShader(program.get(), uTest.get(), 1);



    mt::WindowHandle& window = mt::getWindow();
    while(!window->shouldClose()) 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        mt::submit(vInput.get(), shader.get());

        window->run();
    }

    program->destroy();
    vertexBuffer->destroy();
    indexBuffer->destroy();
    vInput->destroy();
    // uTest->destroy(); 
    shader->destroy();
    
    mt::shutdown();
}

