#include "gl_shader.hpp"
#include "files/file.hpp"

#include <glad/gl.h>


GLShader::GLShader(const char* vertPath, const char* fragPath, const char* geoPath = nullptr) 
{
    const std::vector<char> vertCode = File::ParseFile(vertPath);
    const std::vector<char> fragCode = File::ParseFile(fragPath);

    std::vector<char> geoCode = {};

    if(geoPath != nullptr) 
    {
        geoCode = File::ParseFile(fragPath);
    }

    GLuint vShader, fShader, gShader;

    const char* vertSrc = vertCode.data();
    const char* fragSrc = fragCode.data();
    const char* geoSrc = geoCode.data();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertSrc, NULL);
    glCompileShader(vShader);
    CheckCompilationErrors(vShader, "VERTEX");

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragSrc, NULL);
    glCompileShader(fShader);
    CheckCompilationErrors(fShader, "FRAGMENT");

    if (!geoCode.empty())
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geoSrc, NULL);
        glCompileShader(gShader);
        CheckCompilationErrors(gShader, "GEOMETRY");
    }

    mProgram = glCreateProgram();

    glAttachShader(mProgram, vShader);
    glAttachShader(mProgram, fShader);

    if (!geoCode.empty()) 
    {
        glAttachShader(mProgram, gShader);
    }

    glLinkProgram(mProgram);

    CheckCompilationErrors(mProgram, "PROGRAM");

    // Programs can be cleaned-up now after linking into mProgram.
    //
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    if (!geoCode.empty()) 
    {
        glDeleteShader(gShader);
    }
}

void GLShader::CheckCompilationErrors(GLuint object, std::string type) const
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