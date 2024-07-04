#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "graphics/framebuffer.hpp"
#include "gl_texture.hpp"

#include <glad/gl.h>
#include <iostream>


struct GLRenderbufferBlueprint 
{
    GLuint format;
    GLuint attachmentType;
    uint32_t width;
    uint32_t height;
};

struct GLFramebufferBlueprint 
{
    GLTexture2D texture;
    uint32_t attachment;
    GLRenderbufferBlueprint* renderbufferBlueprint;
};



/**
 * @brief Configures a glFramebuffer and provides utility to bind and draw to the target texture
 * with color, depth or stencil attachments.
 */
class GLFramebuffer final
{
public: 
    GLFramebuffer(GLFramebufferBlueprint blueprint);

    void Resize(const uint32_t width, const uint32_t height);

    void Destroy() noexcept;

private:
    GLuint mFramebuffer;
    GLuint mRenderbuffer;

    GLFramebufferBlueprint& mBlueprint;
};

#endif