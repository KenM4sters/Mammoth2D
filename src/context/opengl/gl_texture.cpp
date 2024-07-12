#include "gl_texture.hpp"


namespace mt 
{

void GLTexture::create(const uint32_t width, const uint32_t height, GLenum internalFormat, TextureFlags flags) 
{


    if(m_flags & TextureFlags::WriteOnly) 
    {
        GL_CHECK(glGenRenderbuffers(1, &m_glHandle));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_glHandle));
        GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, m_internalFormat, m_width, m_height));
        GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE));
        m_isTexture = false;
    } 
    else 
    {
        GL_CHECK(glGenTextures(1, &m_glHandle));
        
        GL_CHECK(glActiveTexture(m_unit));
        GL_CHECK(glBindTexture(m_target, m_glHandle));

        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MIN_FILTER, sampler.m_minFilter));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MAG_FILTER, sampler.m_magFilter));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_S, sampler.m_sWrap));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_T, sampler.m_rWrap));
        GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_R, sampler.m_tWrap));

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

void GLTexture::update(const GLTextureBlueprint& blueprint) 
{
    m_target = blueprint.target;
    m_level = blueprint.level;
    m_width = blueprint.width;
    m_height = blueprint.height;
    m_internalFormat = blueprint.internalFormat;
    m_format = blueprint.format;
    m_type = blueprint.type;

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

void GLTexture::resize(const uint32_t width, const uint32_t height) 
{
    m_width = width;
    m_height = height;

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

void GLTexture::setTextureUnit(const GLuint unit) 
{
    m_unit = unit;
}

void GLTexture::bind() 
{
    GL_CHECK(glActiveTexture(m_unit));
    GL_CHECK(glBindTexture(m_target, m_glHandle));
    m_isBound = true;
}

void GLTexture::release() 
{
    GL_CHECK(glActiveTexture(m_unit));
    GL_CHECK(glBindTexture(m_target, GL_NONE));
    m_isBound = false;
}

void GLTexture::destroy() 
{
    release();
    GL_CHECK(glDeleteTextures(1, &m_glHandle));
}

}