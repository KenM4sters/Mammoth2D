#include "gl_buffer.hpp"


namespace mt 
{

GLVertexBuffer::GLVertexBuffer(const void const* data, const size_t byteSize) 
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLVertexBuffer::setBufferData(const void const* data, const size_t byteSize) 
{
    glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

GLIndexBuffer::GLIndexBuffer(const void const* data, const size_t byteSize) 
{
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void GLVertexBuffer::setBufferData(const void const* data, const size_t byteSize) 
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

GLUniformBuffer::GLUniformBuffer(const void const* data, const size_t byteSize) 
{

}

void GLVertexBuffer::setBufferData(const void const* data, const size_t byteSize) 
{
    glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

}