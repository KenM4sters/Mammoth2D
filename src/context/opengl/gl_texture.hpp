#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP


#include "gl_core.hpp"
#include "./renderer_interface.hpp"


namespace mt 
{

class GLSampler final
{
public:
	explicit GLSampler(GLenum sWrap, GLenum tWrap, GLenum rWrap, 
		GLenum minFilter, GLenum magFilter)
		: m_sWrap{sWrap},
		m_tWrap{tWrap},
		m_rWrap{rWrap},
		m_minFilter{minFilter},
		m_magFilter{magFilter} 
    {

	}

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

/**
 * @brief Interface for GLTexture2D and GLTextureCube.
 */
class GLTexture final 
{
public:
    explicit GLTexture(const GLTextureBlueprint& blueprint)
        : m_id{0}, 
        m_target{blueprint.target}, 
        m_level{blueprint.level}, 
        m_width{blueprint.width}, 
        m_height{blueprint.height},
        m_internalFormat{blueprint.internalFormat}, 
		m_format{blueprint.format}, 
		m_type{blueprint.type} 
    {
        create();
    }

    ~GLTexture() 
    {
        destroy();
    }

	void create();

    void bind(GLenum unit = GL_TEXTURE0);

    void release(GLenum unit = GL_TEXTURE0);

    void resize(const uint32_t& width, const uint32_t& height);
		
	void setSampler(const GLSampler const* sampler);

    void destroy();

    [[nodiscard]] constexpr const GLboolean isBound() const noexcept { return m_isBound; } 
    [[nodiscard]] constexpr const GLuint getId() const noexcept { return m_id; } 
    [[nodiscard]] constexpr const GLenum getTarget() const noexcept { return m_target; } 
    [[nodiscard]] constexpr const GLuint getLevel() const noexcept { return m_level; } 
    [[nodiscard]] constexpr const GLsizei getWidth() const noexcept { return m_width; } 
    [[nodiscard]] constexpr const GLsizei getHeight() const noexcept { return m_height; } 
    [[nodiscard]] constexpr const GLenum getInternalFormat() const noexcept { return m_internalFormat; } 
    [[nodiscard]] constexpr const GLenum getFormat() const noexcept { return m_format; } 
    [[nodiscard]] constexpr const GLenum getType() const noexcept { return m_type; } 

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
};

}


#endif