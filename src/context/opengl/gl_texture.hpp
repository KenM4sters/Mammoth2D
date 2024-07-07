#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP

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
    GLuint dimension;
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
 * @brief Interface for GLTexture2D and GLTextureCube.
 */
class GLTexture 
{
public:
    explicit GLTexture(GLTextureBlueprint blueprint) : mBlueprint{blueprint} {}

    virtual ~GLTexture() {}

    virtual void Resize(const uint32_t width, const uint32_t height) = 0;

    virtual void Destroy() = 0;

    [[nodiscard]] constexpr const GLTextureBlueprint& GetBlueprint() noexcept { return mBlueprint; }

protected:
    GLTextureBlueprint mBlueprint;
};


/**
 * @brief Generates a texture program, sets the sampler and image from the blueprint. 
 */
class GLTexture2D final : public GLTexture
{
public:
    explicit GLTexture2D(GLTextureBlueprint blueprint);

    void Resize(const uint32_t width, const uint32_t height);

    void Destroy() noexcept;

    [[nodiscard]] constexpr const GLuint& GetId() noexcept { return mId; }

private:
    GLuint mId;
};




/**
 * @brief Generates a texture program, sets the sampler and image from the blueprint. 
 */
class GLTextureCube final : public GLTexture
{
public:
    explicit GLTextureCube(GLTextureBlueprint blueprint);

    void Resize(const uint32_t width, const uint32_t height);

    void Destroy() noexcept;

    [[nodiscard]] constexpr const GLuint& GetId() noexcept { return mId; }

private:
    GLuint mId;
};


#endif