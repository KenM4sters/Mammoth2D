#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "gl_texture.hpp"

#include <glad/gl.h>

#include <iostream>


namespace mt 
{

/**
 * @brief Configures a glFramebuffer and provides utility to bind and draw to the target texture
 * with color, depth or stencil attachments.
 */
class GLFrameBuffer final
{
public: 
    GLFrameBuffer()
        : m_frameBuffer{0},
        m_colorAttachment{nullptr} 
    {}

    void create();    

    void resize(const uint32_t width, const uint32_t height);

    void destroy();

    [[nodiscard]] constexpr GLuint getGLHandle() const { return m_frameBuffer; }

private:
    GLuint m_frameBuffer;
    std::unique_ptr<GLTexture> m_colorAttachment;
    
    union 
    {
        GLuint m_renderBuffer;
        std::unique_ptr<GLTexture> m_depthStencilAttachment;
    };
};
}

#endif