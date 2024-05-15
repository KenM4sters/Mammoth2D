#pragma once
#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"

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

    std::shared_ptr<Window> mWindow = nullptr;

    std::shared_ptr<Device> mDevice = nullptr;

    std::unique_ptr<Pipeline> mPipeline = nullptr;

};
}