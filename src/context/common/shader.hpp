#ifndef MAMMOTH_2D_SHADER_RESOURCE_HPP
#define MAMMOTH_2D_SHADER_RESOURCE_HPP

#include "api.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "api.hpp"

namespace mt 
{

  
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