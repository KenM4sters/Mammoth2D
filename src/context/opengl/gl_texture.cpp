#include "gl_texture.hpp"


namespace mt 
{

void GLTexture::create(TargetType target, uint32_t level, InternalFormat internalFormat, uint32_t width, 
    uint32_t height, Format format, ValueType type, uint32_t nMipMaps, uint32_t flags, 
    const Sampler* sampler
) 
{
    m_target = convertToGLTargetType(target);
    m_level = level;
    m_internalFormat = convertToGLInternalFormat(internalFormat);
    m_width = width;
    m_height = height;
    m_format = convertToGLFormat(format);
    m_type = convertToGLValueType(type);
    m_numMipMaps = nMipMaps;
    m_flags = flags; 
    m_sampler = static_cast<const GLSampler*>(sampler);

    if(m_flags & static_cast<uint32_t>(TextureFlags::WriteOnly)) 
    {
        GL_CHECK(glGenRenderbuffers(1, &m_glHandle));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_glHandle));
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, m_internalFormat, m_width, m_height));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE));

        m_isTexture = false;
    } 
    else if(m_sampler)
    {
        GL_CHECK(glGenTextures(1, &m_glHandle));
        
        GL_CHECK(glActiveTexture(0));
        GL_CHECK(glBindTexture(m_target, m_glHandle));

        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_sampler->getMinFilter()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_sampler->getMagFilter()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_S, m_sampler->getAdressModeS()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_T, m_sampler->getAdressModeT()));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_R, m_sampler->getAdressModeR()));

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

        if(m_numMipMaps > 0) 
        {
            GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
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
            for(size_t i = 0; i < 6; i++) 
            {
                GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X + i, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
            }
        }
    }
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