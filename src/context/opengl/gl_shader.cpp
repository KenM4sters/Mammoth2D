#include "gl_shader.hpp"


namespace mt 
{

void GLShader::create(const Program* program, Resource* resources, size_t count) 
{
    m_program = static_cast<const GLProgram*>(program);

    GLResource* res = static_cast<GLResource*>(resources);

    for(size_t i = 0; i < count; i++) 
    {
        std::string name = std::string(res[i].getName());

        m_resources[name] = &res[i];
    }
}

void GLShader::update(std::string name, const Memory* memory) 
{
    m_resources[name]->update(memory);
}

void GLShader::destroy() 
{
    for(const auto& res : m_resources) 
    {
        res.second->destroy();
    }
}

}