#ifndef MAMMOTH_2D_SHADER_RESOURCE_HPP
#define MAMMOTH_2D_SHADER_RESOURCE_HPP

#include "api.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

namespace mt 
{

struct ShaderResource 
{
    const char* name;
    ShaderResourceType type;
    void* data;
};

struct ShaderBlueprint 
{
    std::vector<char> vertCode;
    std::vector<char> fragCode; 
    std::vector<Attribute> attributes;
    std::vector<ShaderResource> resources;
};  

class Shader 
{
public:
    explicit Shader(const ShaderBlueprint& blueprint)
        : m_attributes{blueprint.attributes} 
    {

        

        for(const auto& res : blueprint.resources) 
        {
            m_resources[res.name] = res;
        }
    }


private:
    std::vector<Attribute> m_attributes;
    std::unordered_map<std::string, ShaderResource> m_resources;
};

}


#endif