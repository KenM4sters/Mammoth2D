#include <iostream>

#include "Sources/Program.hpp"


int main(int argc, char** argv) 
{
    Super::Program program = Super::Program(800, 600, "Vulkan 2D");
    program.Init();

    try {
        program.Run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 1;
}