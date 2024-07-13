#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP


#include "gl_core.hpp"
#include "gl_sampler.hpp"

namespace mt 
{


class GLTexture final : public Texture
{
public:
    explicit GLTexture() noexcept
        : m_glHandle{0},
        m_isTexture{true}, 
        m_target{GL_TEXTURE_2D}, 
        m_level{0}, 
        m_internalFormat{GL_RGBA32F}, 
        m_width{0}, 
        m_height{0},
        m_format{GL_RGBA},
        m_type{GL_FLOAT},
        m_numMipMaps{0},
        m_flags{0},
        m_sampler{nullptr}
    {}

    GLTexture(const GLTexture& other) = delete;
    GLTexture& operator=(const GLTexture& other) = delete;

	virtual void create(
        TargetType target,
        uint32_t level,
        InternalFormat internalFormat,
        uint32_t width, 
        uint32_t height, 
        Format format,
        ValueType type,
        uint32_t nMipMaps,
        uint32_t flags,
        const Sampler* sampler
    ) override;

    virtual void resize(uint32_t width, uint32_t height) override;

    virtual void destroy() override;

    [[nodiscard]] constexpr GLboolean isTexture() const noexcept { return m_isTexture; } 
    [[nodiscard]] constexpr GLuint getGLHandle() const noexcept { return m_glHandle; } 
    [[nodiscard]] constexpr GLenum getTarget() const noexcept { return m_target; } 
    [[nodiscard]] constexpr GLuint getLevel() const noexcept { return m_level; } 
    [[nodiscard]] constexpr GLsizei getWidth() const noexcept { return m_width; } 
    [[nodiscard]] constexpr GLsizei getHeight() const noexcept { return m_height; } 
    [[nodiscard]] constexpr GLenum getInternalFormat() const noexcept { return m_internalFormat; } 
    [[nodiscard]] constexpr GLenum getFormat() const noexcept { return m_format; } 
    [[nodiscard]] constexpr GLenum getType() const noexcept { return m_type; } 
    [[nodiscard]] constexpr uint32_t getFlags() const noexcept { return m_flags; } 

private:
    GLuint m_glHandle;

    GLboolean m_isTexture;
    
    GLenum m_target;
    GLuint m_level;
    GLenum m_internalFormat;
    GLenum format;
    GLenum type;
    GLsizei m_width;
    GLsizei m_height;
    GLenum m_format;
    GLenum m_type;
    GLuint m_numMipMaps;

    uint32_t m_flags;

    const GLSampler* m_sampler;
};

}


#endif