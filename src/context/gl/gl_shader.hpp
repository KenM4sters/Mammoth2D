#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "Core.hpp"
#include "graphics/shader.hpp"

#include <glad/gl.h>

#include <string>


/**
 * @brief Manages the compilation of a shader program from a mandatory vertex 
 * and fragment shader file paths, and optionally a geometry shader file path.
 * Holds the glProgram and nothing else. All functionality is managed externally. 
 */
class GLShader final : public IShader
{
public:
    explicit GLShader(const char* vertPath, const char* fragPath, const char* geoPath = nullptr);

private:
    void CheckCompilationErrors(GLuint object, std::string type) const;

private:
    GLuint mProgram;
};

#endif 