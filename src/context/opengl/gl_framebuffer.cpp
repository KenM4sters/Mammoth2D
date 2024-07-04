#include "gl_framebuffer.hpp"

GLFramebuffer::GLFramebuffer(GLFramebufferBlueprint blueprint)
    : mBlueprint{blueprint}
{

    const GLTextureBlueprint& textureBlueprint = mBlueprint.texture.GetBlueprint();

    glGenFramebuffers(1, &mFramebuffer);
 
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

}

void GLFramebuffer::Resize(const uint32_t width, const uint32_t height) 
{
    
}

void GLFramebuffer::Destroy() noexcept 
{
    glDeleteFramebuffers(1, &mFramebuffer);

    if(mBlueprint.renderbufferBlueprint != nullptr) 
    {
        glDeleteRenderbuffers(1, &mRenderbuffer);
    }
}