#include "gl_frame_buffer.hpp"

namespace mt 
{

void GLFrameBuffer::create(const Attachment* attachments, size_t count) 
{
    GL_CHECK(glGenFramebuffers(1, &m_frameBuffer));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

    for(size_t i = 0; i < count; i++) 
    {
        const GLTexture* texture = static_cast<GLTexture*>(attachments[i].pTexture); 

        if(texture->getFormat()) 
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, mBlueprint.attachment, GL_TEXTURE_2D, texture->GetId(), mBlueprint.level);
        }
    }

    if(texture) 
    {        
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

void GLFrameBuffer::resize(const uint32_t width, const uint32_t height) 
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

void GLFrameBuffer::destroy() noexcept 
{
    glDeleteFramebuffers(1, &mFramebuffer);

    if(mBlueprint.renderbufferBlueprint != nullptr) 
    {
        glDeleteRenderbuffers(1, &mRenderbuffer);
    }

    delete mBlueprint.renderbufferBlueprint;
}

}