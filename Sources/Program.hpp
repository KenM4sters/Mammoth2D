#pragma once
#include "Window.hpp"
#include "Pipeline.hpp"

namespace Super
{
class Program 
{
public:
    Program(uint32_t width, uint32_t height, const char* name);
    ~Program();

    void Init();

    void Run();

private:

    std::unique_ptr<Window> mWindow = nullptr;

    Pipeline mPipeline{"Shaders/simple.vert.spv", "Shaders/simple.frag.spv"};

};
}