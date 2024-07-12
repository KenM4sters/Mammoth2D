#ifndef MAMMMOTH_2D_GL_SHADER_HPP
#define MAMMMOTH_2D_GL_SHADER_HPP

#include <mammoth/mamoth.hpp>
#include "gl_resource.hpp"

#include <unordered_map>

namespace mt 
{

class GLShader : public Shader 
{
public: 
    explicit GLShader() noexcept {}

    virtual void create(Program& program, const Resource* resources, size_t count) override;

    virtual void update(const char* name, const Memory* memory) override;

    virtual void destroy() override;

    [[nodiscard]] const std::unordered_map<const char*, std::unique_ptr<GLResource>>& getResources() const { return m_resources; }

private:
    std::unordered_map<const char*, std::unique_ptr<GLResource>> m_resources;
};

}



#endif