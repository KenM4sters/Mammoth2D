#ifndef MAMMOTH_2D_GL_CORE_HPP
#define MAMMOTH_2D_GL_CORE_HPP

#include <glad/gl.h>
#include <string>
#include <iostream>

#define GL_CHECK(stmt) do { \
    stmt; \
    CheckGLError(#stmt, __FILE__, __LINE__); \
} while (0)



std::string GetGLErrorString(GLenum error) 
{
    switch (error) 
    {
        case GL_NO_ERROR:          return "GL_NO_ERROR";
        case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:                   return "Unknown Error";
    }
}


void CheckGLError(const char* stmt, const char* file, int line) 
{
    GLenum error = glGetError();

    if (error != GL_NO_ERROR) 
    {
        std::cerr << "OpenGL error in file " << file << " at line " << line << ": " 
                  << GetGLErrorString(error) << " (" << error << ") in statement: " << stmt << std::endl;
    }
}


#endif