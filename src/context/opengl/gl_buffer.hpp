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

    virtual void create(const Memory* memeory, uint32_t flags) override;

    virtual void update(const Memory* memory, size_t byteOffset) override;

    virtual void destroy() override;

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_vbo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_vbo;
    size_t m_byteSize;
};

class GLIndexBuffer final : public IndexBuffer
{
public:
    explicit GLIndexBuffer() noexcept 
        : m_ebo{0},
        m_byteSize{0}
    {}

    GLIndexBuffer(const GLIndexBuffer& other) = delete;
    GLIndexBuffer& operator=(const GLIndexBuffer& other) = delete;

    virtual void create(const Memory* memory, uint32_t flags) override;

    virtual void update(const Memory* memory, size_t byteOffset) override;

    virtual void destroy() override;

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_ebo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_ebo;
    size_t m_byteSize;
};

class GLUniformBuffer final : public UniformBuffer
{
public:
    explicit GLUniformBuffer() noexcept 
        : m_ubo{0},
        m_byteSize{0}
    {}

    GLUniformBuffer(const GLUniformBuffer& other) = delete;
    GLUniformBuffer& operator=(const GLUniformBuffer& other) = delete;
    GLUniformBuffer(GLUniformBuffer&& other) = default;
    GLUniformBuffer& operator=(GLUniformBuffer&& other) = default;

    virtual void create(const Memory* memeory, uint32_t flags) override;

    virtual void update(const Memory* memory, size_t byteOffset) override;

    virtual void destroy() override;

    [[nodiscard]] constexpr const GLuint& GetGLHandle() const noexcept { return m_ubo; }
    [[nodiscard]] constexpr const size_t& GetByteSize() const noexcept { return m_byteSize; }

private:
    GLuint m_ubo;
    size_t m_byteSize;
};

}

#endif