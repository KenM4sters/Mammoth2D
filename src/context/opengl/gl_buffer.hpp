#ifndef MAMMOTH_2D_GL_BUFFER_HPP
#define MAMMOTH_2D_GL_BUFFER_HPP

#include "gl_core.hpp"

namespace mt
{

struct GLVertexBuffer final 
{   
    void create(const void const* data, const size_t byteSize) noexcept;

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    GLuint vbo;
    size_t size;
};

struct GLIndexBuffer final 
{
    void create(const void const* data, const size_t byteSize) noexcept;

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    GLuint ebo;
    size_t size;
};

struct GLUniformBuffer final 
{
    void create(const void const* data, const size_t byteSize) noexcept;

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    GLuint ubo;
    size_t size;
};

}

#endif