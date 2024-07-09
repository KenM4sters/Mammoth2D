#include "gl_texture.hpp"


namespace mt 
{

void GLTexture::create() 
{
    GL_CHECK(glGenTextures(1, &m_id));
    GL_CHECK(glBindTexture(m_target, m_id));
    GL_CHECK(glTexImage2D(m_target, m_level, m_internalFormat, m_width, m_height, 0, m_format, m_type, NULL));
    glBindTexture(m_target, 0);
}

void GLTexture::bind(GLenum unit = GL_TEXTURE0) 
{
    glActiveTexture(unit);
    GL_CHECK(glBindTexture(m_target, m_id));
    m_isBound = true;

}

void GLTexture::release(GLenum unit = GL_TEXTURE0) 
{
    glActiveTexture(unit);
    glBindTexture(m_target, 0);
    m_isBound = false;
}

void GLTexture::resize(const uint32_t& width, const uint32_t& height) 
{

}
    
void GLTexture::setSampler(const GLSampler const* sampler) 
{
    GL_CHECK(glBindTexture(m_target, m_id));
    GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MIN_FILTER, sampler->m_minFilter));
    GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_MAG_FILTER, sampler->m_magFilter));
    GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_S, sampler->m_sWrap));
    GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_T, sampler->m_rWrap));
    GL_CHECK(glSamplerParameteri(m_target, GL_TEXTURE_WRAP_R, sampler->m_tWrap));
}

void GLTexture::destroy() 
{
    release();
    GL_CHECK(glDeleteTextures(1, &m_id));
}

}