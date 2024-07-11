#include "gl_texture.hpp"


namespace mt 
{

void GLTexture::create(const GLTextureBlueprint& blueprint, const GLSampler& sampler) 
{
    m_target = blueprint.target;
    m_level = blueprint.level;
    m_width = blueprint.width;
    m_height = blueprint.height;
    m_internalFormat = blueprint.internalFormat;
    m_format = blueprint.format;
    m_type = blueprint.type;

    GL_CHECK(glGenTextures(1, &m_id));
    
    GL_CHECK(glActiveTexture(m_unit));
    GL_CHECK(glBindTexture(m_target, m_id));

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
    GL_CHECK(glBindTexture(m_target, m_id));
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
    GL_CHECK(glDeleteTextures(1, &m_id));
}

}