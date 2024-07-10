#include "gl_buffer.hpp"


namespace mt 
{

void GLVertexBuffer::create(const void const* data, const size_t byteSize) noexcept 
{

    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &vbo));
}

GLVertexBuffer::~GLVertexBuffer() 
{
    glDeleteBuffers(1, &vbo);
}

void GLIndexBuffer::create(const void const* data, const size_t byteSize) noexcept 
{

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &ebo));
}

void GLUniformBuffer::create(const void const* data, const size_t byteSize) noexcept 
{

    GL_CHECK(glGenBuffers(1, &ubo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, ubo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLUniformBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, ubo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLUniformBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &ubo));
}

}