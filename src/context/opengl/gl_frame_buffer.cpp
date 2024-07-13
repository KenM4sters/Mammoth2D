#include "gl_frame_buffer.hpp"

namespace mt 
{

void GLFrameBuffer::create(const FrameBufferAttachment* attachments, size_t count)
{
    GL_CHECK(glGenFramebuffers(1, &m_frameBuffer));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

    for(size_t i = 0; i < count; i++) 
    {
        const GLTexture* texture = static_cast<const GLTexture*>(attachments[i].pTexture);
        const GLenum attachment = convertToGLAttachmentTarget(attachments[i].attachment);

        if(!texture->isTexture()) 
        {
            GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, texture->getGLHandle()));
        }
        else 
        {
            GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->getGLHandle(), texture->getLevel()));
        }
    }

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE));
}

void GLFrameBuffer::resize(const uint32_t width, const uint32_t height) 
{
}

void GLFrameBuffer::destroy() 
{
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE));
    GL_CHECK(glDeleteFramebuffers(1, &m_frameBuffer));
}

}