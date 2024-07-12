#ifndef MAMMOTH_2D_GL_FRAME_BUFFER_HPP
#define MAMMOTH_2D_GL_FRAME_BUFFER_HPP

#include "gl_texture.hpp"

#include <glad/gl.h>

#include <iostream>


namespace mt 
{

struct GLFrameBufferBlueprint 
{

};

/**
 * @brief Configures a glFramebuffer and provides utility to bind and draw to the target texture
 * with color, depth or stencil attachments.
 */
class GLFrameBuffer final
{
public: 
    explicit GLFrameBuffer() noexcept
        : m_frameBuffer{0},
        m_attachments{0} 
    {}

    GLFrameBuffer& operator=(const GLFrameBuffer& other) = delete;
    GLFrameBuffer(const GLFrameBuffer& other) = delete;
 
    void create(

    );    

    void resize(const uint32_t width, const uint32_t height);

    void destroy();

    [[nodiscard]] constexpr GLuint getGLHandle() const { return m_frameBuffer; }

private:
    GLuint m_frameBuffer;
    std::vector<std::unique_ptr<GLTexture>> m_attachments;
};
}

#endif