#include <iostream>
#include <Program.hpp>

static GLFWwindow* window = nullptr;

int main(int argc, char** argv) 
{
    auto program = std::make_unique<Super::Program>(800, 600, "Vulkan2D");

    program->Init();
    program->Run();
}