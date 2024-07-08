#ifndef MAMMOTH_2D_RENDERER_INTERFACE_HPP
#define MAMMOTH_2D_RENDERER_INTERFACE_HPP

#include <glad/gl.h>

namespace mt 
{

enum class GraphicsBackend 
{
    OpenGL,
    Vulkan
};


enum class SamplerWrapMode
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

enum class SamplerFilterMode 
{
    Nearest,
    Linear,
    MipNearest,
    MipLinear
};

enum class Dimension 
{
    Texture2D,
    Texture3D,
    TextureCube
};

enum class InternalFormat 
{
    R32,
    R32F,
    RG32,
    RG32F,
    RGB32,
    RGB32F,
    RGBA32,
    RGBA32F
};

enum class Format 
{
    R,
    RG,
    RGB,
    RGBA,
};

enum class Attribute 
{
    Position,
    Normal,
    Tangent,
    BiTangent,
    Weight,
    Indices,
    Color,
    TexCoords
};

enum class UniformType 
{
    Sampler,
    Float,
    Int,
    Vec2f,
    Vec2i,
    Vec3f,
    Vec3i,
    Vec4f,
    Vec4i,
    Mat4x4f,
    Mat3x3f
};

enum class DrawMode 
{
    Arrays,
    Indexed
};

enum class Topology
{
    Triangles,
    TrianglesList,
    Lines,
    LinesList,
    Points
};



/**
 * @brief Info required to construct a Texture instance.
 */
struct TextureBlueprint 
{
    Dimension dimension;
    InternalFormat internalFormat;
    uint32_t width;
    uint32_t height;
    Format format;
    UniformType type;
    const char* data;
    SamplerWrapMode sWrap;
    SamplerWrapMode tWrap;
    SamplerWrapMode rWrap;
    SamplerFilterMode min;
    SamplerFilterMode mag;
};

struct RenderbufferBlueprint 
{
    GLuint internalFormat;
    GLuint format;
    uint32_t width;
    uint32_t height;
};

struct FramebufferBlueprint 
{
    GLTexture* texture;
    uint32_t attachment;
    GLuint level;
    GLRenderbufferBlueprint* renderbufferBlueprint;
};




template<typename T>
[[nodiscard]] constexpr const T ConvertSamplerWrapType(const GraphicsBackend backend, SamplerWrapType wrapType ) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(wrapType) 
        {
            case SamplerWrapType::WrapS: return GL_TEXTURE_WRAP_S; break;
            case SamplerWrapType::WrapT: return GL_TEXTURE_WRAP_T; break;
            case SamplerWrapType::WrapR: return GL_TEXTURE_WRAP_R; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConverSamplerWrapMode(const GraphicsBackend backend, SamplerWrapMode wrapMode) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(wrapMode) 
        {
            case SamplerWrapMode::Repeat : return GL_REPEAT; break;
            case SamplerWrapMode::MirroredRepeat : return GL_MIRRORED_REPEAT; break;
            case SamplerWrapMode::ClampToEdge : return GL_CLAMP_TO_EDGE; break;
            case SamplerWrapMode::ClampToBorder : return GL_CLAMP_TO_BORDER; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertSamplerFilterMode(const GraphicsBackend backend, SamplerFilterMode filterMode) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(filterMode) 
        {
            case SamplerFilterMode::Nearest: return GL_NEAREST; break;
            case SamplerFilterMode::Linear: return GL_LINEAR; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertDimension(const GraphicsBackend backend, Dimension dimension) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(dimension) 
        {
            case Dimension::Texture2D: return GL_TEXTURE_2D; break;
            case Dimension::Texture3D: return GL_TEXTURE_3D; break;
            case Dimension::TextureCube: return GL_TEXTURE_CUBE_MAP; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertInternalFormat(const GraphicsBackend backend, InternalFormat internalFormat) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(internalFormat) 
        {
            
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertFormat(const GraphicsBackend backend, Format format) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(wrapType) 
        {
            case Format::R: return GL_RG ; break;
            case Format::WrapT: return GL_TEXTURE_WRAP_T; break;
            case Format::WrapR: return GL_TEXTURE_WRAP_R; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertDrawMode(const GraphicsBackend backend, DrawMode mode) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(wrapType) 
        {
            case SamplerWrapType::WrapS: return GL_TEXTURE_WRAP_S; break;
            case SamplerWrapType::WrapT: return GL_TEXTURE_WRAP_T; break;
            case SamplerWrapType::WrapR: return GL_TEXTURE_WRAP_R; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertDrawShape(const GraphicsBackend backend, DrawShape shape) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(wrapType) 
        {
            case SamplerWrapType::WrapS: return GL_TEXTURE_WRAP_S; break;
            case SamplerWrapType::WrapT: return GL_TEXTURE_WRAP_T; break;
            case SamplerWrapType::WrapR: return GL_TEXTURE_WRAP_R; break;
        }
    }
}


}


#endif