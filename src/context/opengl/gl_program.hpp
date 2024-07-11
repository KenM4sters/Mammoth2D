#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "gl_core.hpp"

#include <glad/gl.h>

#include <string>


namespace mt 
{
/**
 * @brief Manages the compilation of a shader program from a mandatory vertex 
 * and fragment shader file paths, and optionally a geometry shader file path.
 * Holds the glProgram and nothing else. All functionality is managed externally. 
 */
class GLProgram final
{
public:
    explicit GLProgram() noexcept
        : m_program{0} 
    {}

    void create(const char* vertPath, const char* fragPath);

    void bind() const;

    void release() const;
    
    [[nodiscard]] constexpr GLuint getGLHandle() const noexcept { return m_program; }

private:
    /**
     * @brief Reads source file and returns its contents as a vector of characters.
     * Throws an exception if the file failed to open (check file path).
     * @param filePath path to the file to read from.
     * @return vector of characters read from the file.
     */
    [[nodiscard]] std::vector<char> parseShaderFile(const char* filePath) const;

    /**
     * @brief Checks for shader compilation errors (useful for showing syntax errors).
     * @param object the shader code to run checks against (vShader or fShader).
     * @param type shader stage to run checks against (VERTEX or FRAGMENT). 
     */
    void checkShaderErrors(GLuint object, std::string type) const;

private:
    GLuint m_program;
};

}
#endif 