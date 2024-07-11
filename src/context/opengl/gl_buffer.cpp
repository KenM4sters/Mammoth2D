#include "gl_buffer.hpp"


namespace mt 
{

void GLVertexBuffer::create(const void const* data, const size_t byteSize) noexcept 
{
    m_byteSize = byteSize;

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    m_byteSize = byteSize;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_vbo));
}

GLVertexBuffer::~GLVertexBuffer() 
{
    glDeleteBuffers(1, &m_vbo);
}

void GLIndexBuffer::create(const void const* data, const size_t byteSize) noexcept 
{
    m_byteSize = byteSize;

    GL_CHECK(glGenBuffers(1, &m_ebo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ebo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    m_byteSize = byteSize;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ebo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_ebo));
}

void GLUniformBuffer::create(const void const* data, const size_t byteSize) noexcept 
{
    m_byteSize = byteSize;

    GL_CHECK(glGenBuffers(1, &m_ubo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ubo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLUniformBuffer::update(const size_t offset, const void const* data, const size_t byteSize) 
{
    m_byteSize = byteSize;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ubo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, byteSize, data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLUniformBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_ubo));
}

}