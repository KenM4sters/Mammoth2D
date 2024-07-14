#ifndef MAMMMOTH_2D_GL_SHADER_HPP
#define MAMMMOTH_2D_GL_SHADER_HPP

#include <mammoth/mamoth.hpp>
#include "gl_resource.hpp"
#include "gl_program.hpp"

#include <string>
#include <unordered_map>

namespace mt 
{

class GLShader : public Shader 
{
public: 
    explicit GLShader() noexcept {}

    virtual void create(const Program* program, Resource* resources, size_t count) override;

    virtual void update(std::string name, const Memory* memory) override;

    virtual void destroy() override;

    [[nodiscard]] const GLProgram& getProgram() const { return *m_program; }

    [[nodiscard]] const std::unordered_map<std::string, GLResource*>& getResources() const { return m_resources; }

private:
    const GLProgram* m_program;

    std::unordered_map<std::string, GLResource*> m_resources;
};

}



#endif