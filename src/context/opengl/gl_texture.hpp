#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP


#include "gl_core.hpp"


namespace mt 
{

struct GLSampler final
{
    explicit GLSampler(GLenum sWrap, GLenum tWrap, GLenum rWrap, 
        GLenum minFilter, GLenum magFilter) noexcept
        : m_sWrap{sWrap},
        m_tWrap{tWrap},
        m_rWrap{rWrap},
        m_minFilter{minFilter},
        m_magFilter{magFilter} 
    {}
    
    GLenum m_sWrap;
    GLenum m_tWrap;
    GLenum m_rWrap;
    GLenum m_minFilter;
    GLenum m_magFilter;
};

struct GLTextureBlueprint final
{
    GLenum target;
    GLuint level;
    GLsizei width;
    GLsizei height;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
    GLuint nMipMaps;
};

class GLTexture final 
{
public:
    explicit GLTexture() noexcept
        : m_id{0}, 
        m_target{GL_TEXTURE_2D}, 
        m_level{0}, 
        m_width{0}, 
        m_height{0},
        m_internalFormat{GL_RGBA32F}, 
		m_format{GL_RGBA}, 
		m_type{GL_FLOAT},
        m_unit{GL_TEXTURE0}
    {}

	void create(const GLTextureBlueprint& blueprint, const GLSampler& sampler);

    void update(const GLTextureBlueprint& blueprint);

    void resize(const uint32_t width, const uint32_t height);

    void bind();

    void release();

    void setTextureUnit(const GLuint unit);

    void destroy();

    [[nodiscard]] constexpr GLboolean isBound() const noexcept { return m_isBound; } 
    [[nodiscard]] constexpr GLuint getId() const noexcept { return m_id; } 
    [[nodiscard]] constexpr GLenum getTarget() const noexcept { return m_target; } 
    [[nodiscard]] constexpr GLuint getLevel() const noexcept { return m_level; } 
    [[nodiscard]] constexpr GLsizei getWidth() const noexcept { return m_width; } 
    [[nodiscard]] constexpr GLsizei getHeight() const noexcept { return m_height; } 
    [[nodiscard]] constexpr GLenum getInternalFormat() const noexcept { return m_internalFormat; } 
    [[nodiscard]] constexpr GLenum getFormat() const noexcept { return m_format; } 
    [[nodiscard]] constexpr GLenum getType() const noexcept { return m_type; } 
    [[nodiscard]] constexpr GLenum getTextureUnit() const noexcept { return m_unit; } 

private:
    GLuint m_id;
    GLenum m_target;
    GLuint m_level;
    GLsizei m_width;
    GLsizei m_height;
    GLenum m_internalFormat;
    GLenum m_format;
    GLenum m_type;
    GLboolean m_isBound;
    GLuint m_unit;
};

}


#endif