#include "gl_sampler.hpp"


namespace mt 
{

void GLSampler::create(SamplerAddressMode addressModeS, SamplerAddressMode addressModeT, 
    SamplerAddressMode addressModeR, SamplerFilterMode minFilter, SamplerFilterMode magFilter
) 
{
    m_addressModeS = convertToGLAddressMode(addressModeS);
    m_addressModeT = convertToGLAddressMode(addressModeT);
    m_addressModeR = convertToGLAddressMode(addressModeR);
    m_minFilter = convertToGLFilterMode(minFilter);
    m_magFilter = convertToGLFilterMode(magFilter);

    GL_CHECK(glGenSamplers(1, &m_glHandle));
    GL_CHECK(glBindSampler(1, m_glHandle));

    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_S, m_addressModeS));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_T, m_addressModeT));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_R, m_addressModeR));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MIN_FILTER, m_magFilter));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MAG_FILTER, m_magFilter));
    
    GL_CHECK(glBindSampler(0, m_glHandle));
}

void GLSampler::update(SamplerAddressMode addressModeS, SamplerAddressMode addressModeT, 
    SamplerAddressMode addressModeR, SamplerFilterMode minFilter, SamplerFilterMode magFilter
) 
{
    m_addressModeS = convertToGLAddressMode(addressModeS);
    m_addressModeT = convertToGLAddressMode(addressModeT);
    m_addressModeR = convertToGLAddressMode(addressModeR);
    m_minFilter = convertToGLFilterMode(minFilter);
    m_magFilter = convertToGLFilterMode(magFilter);

    GL_CHECK(glBindSampler(1, m_glHandle));

    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_S, m_addressModeS));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_T, m_addressModeT));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_R, m_addressModeR));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MIN_FILTER, m_magFilter));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MAG_FILTER, m_magFilter));
    
    GL_CHECK(glBindSampler(0, m_glHandle));
}

void GLSampler::detroy() 
{
    glDeleteSamplers(1, &m_glHandle);
}

}