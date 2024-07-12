#include "gl_shader.hpp"


namespace mt 
{

void GLShader::create(Program& program, const Resource* resources, size_t count) 
{
    const GLResource* res = static_cast<const GLResource*>(resources);

    for(size_t i = 0; i < count; i++) 
    {
        const char* name = res[i].getName();

        m_resources[name] = std::make_unique<GLResource>(res[i]);
    }
}

void GLShader::update(const char* name, const Memory* memory) 
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