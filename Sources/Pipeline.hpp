#pragma once
#include <fstream>
#include <vector>
namespace Super 
{
class Pipeline 
{
public:
    Pipeline(const char* vertSrc, const char* fragSrc);
    ~Pipeline();

    // This class should not be copied or moved.
    Pipeline(const Pipeline& other) = delete;
    Pipeline operator=(const Pipeline& other) = delete;
    
    void CreateGraphicsPipeline(const char* vertSrc, const char* fragSrc);

private:
    // Reads the shader code from a file and returns the code as a vector of characters.
    const std::vector<char> ReadFromFile(const char* filePath) const;

    
};
}