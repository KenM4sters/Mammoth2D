#include "gl_buffer.hpp"


namespace mt 
{

void GLVertexBuffer::create(const Memory* memory, uint32_t flags) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, m_byteSize, memory->data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::update(const Memory* memory, size_t byteOffset) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, byteOffset, m_byteSize, memory->data));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void GLVertexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_vbo));
}




void GLIndexBuffer::create(const Memory* memory, uint32_t flags) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glGenBuffers(1, &m_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_byteSize, memory->data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::update(const Memory* memory, size_t byteOffset) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
    GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, byteOffset, m_byteSize, memory->data));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void GLIndexBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_ebo));
}





void GLUniformBuffer::create(const Memory* memory, uint32_t flags) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glGenBuffers(1, &m_ubo));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, m_ubo));
    GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, m_byteSize, memory->data, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void GLUniformBuffer::update(const Memory* memory, size_t byteOffset) 
{
    m_byteSize = memory->byteSize;

    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, m_ubo));
    GL_CHECK(glBufferSubData(GL_UNIFORM_BUFFER, byteOffset, m_byteSize, memory->data));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void GLUniformBuffer::destroy() 
{
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    GL_CHECK(glDeleteBuffers(1, &m_ubo));
}
}