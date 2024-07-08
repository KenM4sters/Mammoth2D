#ifndef MAMMOTH_2D_GL_TEXTURE_2D_HPP
#define MAMMOTH_2D_GL_TEXTURE_2D_HPP

#include <glad/gl.h>


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

    [[nodiscard]] constexpr const GLuint& GetId() const noexcept { return mId; }

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