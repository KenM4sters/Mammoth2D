#ifndef MAMMOTH_2D_GL_SHADER_HPP
#define MAMMOTH_2D_GL_SHADER_HPP

#include "gl_texture.hpp"

#include <glad/gl.h>

#include <iostream>


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

    [[nodiscard]] constexpr const GLFramebufferBlueprint& GetBlueprint() const { return mBlueprint; } 

private:
    GLuint mFramebuffer;
    GLuint mRenderbuffer;

    GLFramebufferBlueprint mBlueprint;
};

#endif