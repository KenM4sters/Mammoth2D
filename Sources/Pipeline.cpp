#include <cassert>
#include <iostream>

#include "Pipeline.hpp"

namespace Super 
{
Pipeline::Pipeline(const char* vertSrc, const char* fragSrc) 
{
    CreateGraphicsPipeline(vertSrc, fragSrc);
}

Pipeline::~Pipeline() 
{

}

const std::vector<char> Pipeline::ReadFromFile(const char* filePath) const 
{
    std::ifstream file{filePath, std::ios::ate | std::ios::binary};

    assert(file.is_open() && "File could not be opened!"); // check for errors - if thrown, double check file path.

    size_t fileSize = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

void Pipeline::CreateGraphicsPipeline(const char* vertSrc, const char* fragSrc) 
{
    auto vertCode = ReadFromFile(vertSrc);
    auto fragCode = ReadFromFile(fragSrc);

    std::cout << vertCode.size() << std::endl;
    std::cout << fragCode.size() << std::endl;
}

}