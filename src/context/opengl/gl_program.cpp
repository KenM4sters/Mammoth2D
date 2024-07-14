#include "gl_program.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>


namespace mt 
{

void GLProgram::create(const char* vertPath, const char* fragPath) 
{
    const std::vector<char> vertCode = parseShaderFile(vertPath);
    const std::vector<char> fragCode = parseShaderFile(fragPath);

    GLuint vShader, fShader;

    const char* vertSrc = vertCode.data();
    const char* fragSrc = fragCode.data();

    // vShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vShader, 1, &vertSrc, NULL);
    // glCompileShader(vShader); 
    // checkShaderErrors(vShader, "VERTEX");

    // fShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fShader, 1, &fragSrc, NULL);
    // glCompileShader(fShader);
    // checkShaderErrors(fShader, "FRAGMENT");

    // m_program = glCreateProgram();

    // glAttachShader(m_program, vShader);
    // glAttachShader(m_program, fShader);
    // glLinkProgram(m_program);

    // checkShaderErrors(m_program, "PROGRAM");

    // // Programs can be cleaned-up now after linking into m_program.
    // //
    // GL_CHECK(glDeleteShader(vShader));
    // GL_CHECK(glDeleteShader(fShader));
}

void GLProgram::destroy() 
{
    GL_CHECK(glUseProgram(0));
    GL_CHECK(glDeleteProgram(m_program));
}

std::vector<char> GLProgram::parseShaderFile(const char* filePath) const
{
    std::ifstream file{filePath, std::ios::ate | std::ios::binary};

    assert(file.is_open() && "File could not be opened!"); // check for errors - if thrown, double check file path.

    size_t fileSize = static_cast<size_t>(file.tellg());

    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}


void GLProgram::checkShaderErrors(GLuint object, std::string type) const
{
    int success;

    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
}