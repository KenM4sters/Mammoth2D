#ifndef MAMMOTH_2D_GL_BUFFER_HPP
#define MAMMOTH_2D_GL_BUFFER_HPP

#include <glad/gl.h>

#include <vector>

namespace mt
{

class GLVertexBuffer final 
{
public:
    explicit GLVertexBuffer(const void const* data, const size_t byteSize);
    ~GLVertexBuffer();

    void setBufferData(const void const* data, const size_t byteSize) noexcept;

private:
    GLuint vbo;
};

class GLIndexBuffer final 
{
public:
    explicit GLIndexBuffer(const void const* data, const size_t byteSize);
    ~GLIndexBuffer();

    void setBufferData(const void const* data, const size_t byteSize) noexcept;

private:
    GLuint ebo;
};

class GLUniformBuffer final 
{
public:
    explicit GLUniformBuffer(const void const* data, const size_t byteSize);

    void setBufferData(const void const* data, const size_t byteSize) noexcept;

private:
    GLuint ubo;
};

}

#endif