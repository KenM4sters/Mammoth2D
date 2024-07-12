#include "gl_sampler.hpp"


namespace mt 
{

void GLSampler::create(const GLSamplerBlueprint& blueprint) 
{
    m_addressModeS = blueprint.addressModeS;
    m_addressModeT = blueprint.addressModeT;
    m_addressModeR = blueprint.addressModeR;
    m_minFilter = blueprint.minFilter;
    m_magFilter = blueprint.magFilter;

    GL_CHECK(glGenSamplers(1, &m_glHandle));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_S, m_addressModeS));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_T, m_addressModeT));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_WRAP_R, m_addressModeR));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MIN_FILTER, m_magFilter));
    GL_CHECK(glSamplerParameteri(m_glHandle, GL_TEXTURE_MAG_FILTER, m_magFilter));
}

void GLSampler::destroy() 
{
    GL_CHECK(glDeleteSamplers(1, &m_glHandle));
}

}