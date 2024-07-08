#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "Core.hpp"

#include <glad/gl.h>

#include <string>


/**
 * @brief Manages the compilation of a shader program from a mandatory vertex 
 * and fragment shader file paths, and optionally a geometry shader file path.
 * Holds the glProgram and nothing else. All functionality is managed externally. 
 */
class GLShaderProgram final
{
public:
    explicit GLShaderProgram(const char* vertPath, const char* fragPath, const char* geoPath = nullptr);

    [[nodiscard]] constexpr const GLuint& GetProgram() noexcept { return mProgram; }

    /**
     * @brief Reads source file and returns its contents as a vector of characters.
     * Throws an exception if the file failed to open (check file path).
     * @param filePath path to the file to read from.
     * @return vector of characters read from the file.
     */
    [[nodiscard]] std::vector<char> ParseShaderFile(const char* filePath) const;

private:
    void CheckCompilationErrors(GLuint object, std::string type) const;

private:
    GLuint mProgram;
};

#endif 