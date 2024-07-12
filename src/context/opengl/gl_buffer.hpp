#ifndef MAMMOTH_2D_GL_BUFFER_HPP
#define MAMMOTH_2D_GL_BUFFER_HPP

#include "gl_core.hpp"

namespace mt
{

class GLVertexBuffer final : public VertexBuffer 
{ 
public:
    explicit GLVertexBuffer() noexcept 
        : m_vbo{0},
        m_byteSize{0}
    {}

    GLVertexBuffer(const GLVertexBuffer& other) = delete;
    GLVertexBuffer& operator=(const GLVertexBuffer& other) = delete;

    void virtual create(const Memory* memeory, VertexBufferFlags flags) override;

    void virtual update(const Memory* memory, size_t byteOffset) override;

    void virtual destroy() override;

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_vbo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_vbo;
    size_t m_byteSize;
};

class GLIndexBuffer final 
{
    explicit GLIndexBuffer() noexcept 
    {}

    GLIndexBuffer(const GLIndexBuffer& other) = delete;
    GLIndexBuffer& operator=(const GLIndexBuffer& other) = delete;

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
    explicit GLUniformBuffer() noexcept 
    {}

    GLUniformBuffer(const GLUniformBuffer& other) = delete;
    GLUniformBuffer& operator=(const GLUniformBuffer& other) = delete;

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