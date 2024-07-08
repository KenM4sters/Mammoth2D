#include "gl_framebuffer.hpp"

GLFramebuffer::GLFramebuffer(GLFramebufferBlueprint blueprint)
    : mBlueprint{blueprint}
{

    const GLTextureBlueprint& textureBlueprint = mBlueprint.texture->GetBlueprint();
    const GLTexture2D* texture = dynamic_cast<GLTexture2D*>(mBlueprint.texture);

    if(texture) 
    {        
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, mBlueprint.attachment, GL_TEXTURE_2D, texture->GetId(), mBlueprint.level);

        if(mBlueprint.renderbufferBlueprint) 
        {
            glGenRenderbuffers(1, &mRenderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, mRenderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, mBlueprint.renderbufferBlueprint->format, mBlueprint.renderbufferBlueprint->width, mBlueprint.renderbufferBlueprint->height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, mBlueprint.renderbufferBlueprint->attachmentType, GL_RENDERBUFFER, mRenderbuffer);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE);
}

void GLFramebuffer::Resize(const uint32_t width, const uint32_t height) 
{

    mBlueprint.texture->Resize(width, height);

    if(mBlueprint.renderbufferBlueprint) 
    {
        mBlueprint.renderbufferBlueprint->width = width;
        mBlueprint.renderbufferBlueprint->height = height;

        glGenRenderbuffers(1, &mRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, mRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, mBlueprint.renderbufferBlueprint->format, mBlueprint.renderbufferBlueprint->width, mBlueprint.renderbufferBlueprint->height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, mBlueprint.renderbufferBlueprint->attachmentType, GL_RENDERBUFFER, mRenderbuffer);
    }
}

void GLFramebuffer::Destroy() noexcept 
{
    glDeleteFramebuffers(1, &mFramebuffer);

    if(mBlueprint.renderbufferBlueprint != nullptr) 
    {
        glDeleteRenderbuffers(1, &mRenderbuffer);
    }

    delete mBlueprint.renderbufferBlueprint;
}