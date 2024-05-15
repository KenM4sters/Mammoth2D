#pragma once
#include <fstream>
#include <vector>
#include "Device.hpp"

namespace Super 
{

struct Pipeline_Desc 
{

};

class Pipeline 
{
public:
    Pipeline(std::shared_ptr<Device> device, Pipeline_Desc desc, const char* vertSrc, const char* fragSrc);
    ~Pipeline();

    // This class should not be copied or moved.
    Pipeline(const Pipeline& other) = delete;
    Pipeline operator=(const Pipeline& other) = delete;

    static Pipeline_Desc DefaultPipelineDesc(uint32_t width, uint32_t height);
    
    void CreateGraphicsPipeline(Pipeline_Desc& desc, const char* vertSrc, const char* fragSrc);

private:
    // Reads the shader code from a file and returns the code as a vector of characters.
    const std::vector<char> ReadFromFile(const char* filePath) const;

    void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    std::shared_ptr<Device> mDevice = nullptr;
    VkPipeline mPipeline;
    VkShaderModule mVertexModule;
    VkShaderModule mFragmentModules;
};
}