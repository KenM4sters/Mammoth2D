#ifndef MAMMOTH_2D_GL_BUFFER_HPP
#define MAMMOTH_2D_GL_BUFFER_HPP

#include "gl_core.hpp"

namespace mt
{

class GLVertexBuffer final 
{ 
    explicit GLVertexBuffer::GLVertexBuffer() noexcept {}

    void create(const void const* data, const size_t byteSize);

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_vbo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_vbo;
    size_t m_byteSize;
};

class GLIndexBuffer final 
{
    explicit GLIndexBuffer::GLIndexBuffer() noexcept {}

    void create(const void const* data, const size_t byteSize);

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_ebo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_ebo;
    size_t m_byteSize;
};

class GLUniformBuffer final 
{
    explicit GLUniformBuffer::GLUniformBuffer() noexcept {}

    void create(const void const* data, const size_t byteSize);

    void update(const size_t offset, const void const* data, const size_t byteSize);

    void destroy();

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_ubo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_ubo;
    size_t m_byteSize;
};

}

#endif