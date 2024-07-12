#include "gl_texture.hpp"


namespace mt 
{

void GLTexture::create(uint32_t width, uint32_t height, GLenum internalFormat, TextureFlags flags, const GLSampler* sampler) 
{
    if(m_flags & TextureFlags::WriteOnly) 
    {
        GL_CHECK(glGenRenderbuffers(1, &m_glHandle));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_glHandle));
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, m_internalFormat, m_width, m_height));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE));

        m_isTexture = false;
    } 
    else if(sampler)
    {
        GL_CHECK(glGenTextures(1, &m_glHandle));
        
        GL_CHECK(glActiveTexture(m_unit));
        GL_CHECK(glBindTexture(m_target, m_glHandle));

        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MIN_FILTER, sampler->getMinFilter()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MAG_FILTER, sampler->getMagFilter()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_S, sampler->getAdressModeS()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_T, sampler->getAdressModeT()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_R, sampler->getAdressModeR()));

        if(m_target == GL_TEXTURE_2D) 
        {
            GL_CHECK(glTexImage2D(m_target, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
        }
        else if(m_target == GL_TEXTURE_CUBE_MAP) 
        {
            for(int i = 0; i < 6; i++) 
            {
                GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X + i, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
            }
        }
        
        GL_CHECK(glBindTexture(m_target, GL_NONE));

        m_isTexture = true;
    }

}


void GLTexture::resize(uint32_t width, uint32_t height) 
{
    m_width = width;
    m_height = height;

    if(!m_isTexture) 
    {
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_glHandle));
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, m_internalFormat, m_width, m_height));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE));
    }
    else 
    {
        if(m_target == GL_TEXTURE_2D) 
        {
            GL_CHECK(glTexImage2D(m_target, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
        }
        else if(m_target == GL_TEXTURE_CUBE_MAP) 
        {
            for(int i = 0; i < 6; i++) 
            {
                GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X + i, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
            }
        }
    }
}

void GLTexture::setTextureUnit(const GLuint unit) 
{
    m_unit = unit;
}

void GLTexture::destroy() 
{
    GL_CHECK(glBindTexture(m_target, 0));

    if(m_isTexture) 
    {
        GL_CHECK(glDeleteTextures(1, &m_glHandle));
    }
    else 
    {
        GL_CHECK(glDeleteRenderbuffers(1, &m_glHandle));
    }
}

}