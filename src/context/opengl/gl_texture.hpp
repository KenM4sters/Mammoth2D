#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP


#include "gl_core.hpp"


namespace mt 
{

struct GLTextureBlueprint 
{
    GLboolean isTexture;
    GLenum target;
    GLuint level;
    GLsizei width;
    GLsizei height;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
    GLboolean isBound;
    GLenum attachment;
    GLuint unit;
    uint32_t flags;
};


class GLTexture final 
{
public:
    explicit GLTexture() noexcept
        : m_glHandle{0},
        m_isTexture{true}, 
        m_target{GL_TEXTURE_2D}, 
        m_level{0}, 
        m_width{0}, 
        m_height{0},
        m_internalFormat{GL_RGBA32F}, 
		m_format{GL_RGBA}, 
		m_type{GL_FLOAT},
        m_unit{GL_TEXTURE0}
    {}

    GLTexture(const GLTexture& other) = delete;
    GLTexture& operator=(const GLTexture& other) = delete;

	void create(
        const uint32_t width, 
        const uint32_t height, 
        GLenum internalFormat,
        TextureFlags flags
        );

    void update(const uint32_t width, const uint32_t height);

    void resize(const uint32_t width, const uint32_t height);

    void bind();

    void release();

    void setTextureUnit(const GLuint unit);

    void destroy();

    [[nodiscard]] constexpr GLboolean isBound() const noexcept { return m_isBound; } 
    [[nodiscard]] constexpr GLboolean isTexture() const noexcept { return m_isTexture; } 
    [[nodiscard]] constexpr GLuint getGLHandle() const noexcept { return m_glHandle; } 
    [[nodiscard]] constexpr GLenum getTarget() const noexcept { return m_target; } 
    [[nodiscard]] constexpr GLuint getLevel() const noexcept { return m_level; } 
    [[nodiscard]] constexpr GLsizei getWidth() const noexcept { return m_width; } 
    [[nodiscard]] constexpr GLsizei getHeight() const noexcept { return m_height; } 
    [[nodiscard]] constexpr GLenum getInternalFormat() const noexcept { return m_internalFormat; } 
    [[nodiscard]] constexpr GLenum getFormat() const noexcept { return m_format; } 
    [[nodiscard]] constexpr GLenum getType() const noexcept { return m_type; } 
    [[nodiscard]] constexpr GLenum getTextureUnit() const noexcept { return m_unit; } 

private:
    GLuint m_glHandle;
    GLboolean m_isTexture;
    GLenum m_target;
    GLuint m_level;
    GLsizei m_width;
    GLsizei m_height;
    GLenum m_internalFormat;
    GLenum m_format;
    GLenum m_type;
    GLboolean m_isBound;
    GLenum m_attachment;
    GLuint m_unit;
    uint32_t m_flags;
};

}


#endif