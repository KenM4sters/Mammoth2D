#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP

#include "graphics/texture.hpp"

#include <glad/gl.h>

/**
 * @brief Info for the min, mag filters and wrapping modes for a sampler. Required
 * by a GLTextureBlueprint.
 */
struct GLSamplerBlueprint 
{
    GLuint minFilter;
    GLuint magFilter;
    GLuint sWrap;
    GLuint tWrap;
    GLuint rWrap;
};

/**
 * @brief Info required to construct a GLTexture instance.
 */
struct GLTextureBlueprint 
{
    GLuint format;
    uint32_t width;
    uint32_t height;
    GLuint nChannels;
    GLuint type;
    GLboolean generateMipMaps;
    const char* data;
    GLSamplerBlueprint samplerBlueprint;
};


/**
 * @brief Generates a texture program, sets the sampler and image from the blueprint. 
 */
class GLTexture2D final : public ITexture2D 
{
public:
    explicit GLTexture2D(GLTextureBlueprint blueprint);

    void Resize(const uint32_t width, const uint32_t height);

    void Destroy() noexcept;

private:
    GLuint mProgram;

    GLTextureBlueprint& mBlueprint;
};




/**
 * @brief Generates a texture program, sets the sampler and image from the blueprint. 
 */
class GLTextureCube final : public ITextureCube
{
public:
    explicit GLTextureCube(GLTextureBlueprint blueprint);

    void Resize(const uint32_t width, const uint32_t height);

    void Destroy() noexcept;

private:
    GLuint mProgram;
    
    GLTextureBlueprint& mBlueprint;
};


#endif