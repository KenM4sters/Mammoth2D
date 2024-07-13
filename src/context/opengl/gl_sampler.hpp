#ifndef MAMMOTH_2D_GL_SAMPLER_HPP
#define MAMMOTH_2D_GL_SAMPLER_HPP

#include "gl_core.hpp"

namespace mt 
{

class GLSampler final : public Sampler
{
public:
    explicit GLSampler() noexcept
        : m_addressModeS{GL_CLAMP_TO_EDGE},
        m_addressModeT{GL_CLAMP_TO_EDGE},
        m_addressModeR{GL_CLAMP_TO_EDGE},
        m_minFilter{GL_LINEAR},
        m_magFilter{GL_LINEAR} 
    {}

    virtual void create(
        SamplerAddressMode addressModeS,
        SamplerAddressMode addressModeT,
        SamplerAddressMode addressModeR,
        SamplerFilterMode minFilter,
        SamplerFilterMode magFilter
    ) override;

    virtual void update(
        SamplerAddressMode addressModeS,
        SamplerAddressMode addressModeT,
        SamplerAddressMode addressModeR,
        SamplerFilterMode minFilter,
        SamplerFilterMode magFilter
    ) override;

    virtual void detroy() override;

    [[nodiscard]] constexpr GLuint getGLHandle() const { return m_glHandle; }
    [[nodiscard]] constexpr GLenum getAdressModeS() const { return m_addressModeS; }
    [[nodiscard]] constexpr GLenum getAdressModeT() const { return m_addressModeT; }
    [[nodiscard]] constexpr GLenum getAdressModeR() const { return m_addressModeR; }
    [[nodiscard]] constexpr GLenum getMinFilter() const { return m_minFilter; }
    [[nodiscard]] constexpr GLenum getMagFilter() const { return m_magFilter; }

private:
    GLuint m_glHandle;
    GLenum m_addressModeS;
    GLenum m_addressModeT;
    GLenum m_addressModeR;
    GLenum m_minFilter;
    GLenum m_magFilter;
};
}

#endif