#include "gl_buffer.hpp"


namespace mt 
{

GLVertexBuffer::GLVertexBuffer(const void const* data, const size_t byteSize) 
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

GLVertexBuffer::~GLVertexBuffer() 
{
    glDeleteBuffers(1, &vbo);
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

GLIndexBuffer::~GLIndexBuffer() 
{
    glDeleteBuffers(1, &ebo);
}

void GLIndexBuffer::setBufferData(const void const* data, const size_t byteSize) 
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

GLUniformBuffer::GLUniformBuffer(const void const* data, const size_t byteSize) 
{
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
}

GLUniformBuffer::~GLUniformBuffer() 
{
    glDeleteBuffers(1, &ubo);
}

void GLUniformBuffer::setBufferData(const void const* data, const size_t byteSize) 
{
    glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

}