#ifndef MAMMOTH_2D_RENDERER_INTERFACE_HPP
#define MAMMOTH_2D_RENDERER_INTERFACE_HPP


namespace mt 
{

enum class GraphicsBackend 
{
    OpenGL,
    Vulkan
};

enum class SamplerWrapType 
{
    WrapS,
    WrapT,
    WrapR
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
    Linear
};

enum class Dimension 
{
    Texture2D,
    Texture3D,
    TextureCube
};

enum class TextureInternalFormat 
{
    R16F,
    RG,
    RG16F,
    RGB,
    RGB16F,
    RBG32F,
    RGBA,
    RGBA16F,
    RGBA32F,
    DepthStencil16F 
};

enum class TextureFormat 
{
    R,
    RG,
    RGB,
    RGBA,
};


enum class DrawMode 
{
    Arrays,
    Indexed
};

enum class DrawShape
{
    Triangles,
    TrianglesList,
    TrianglesFan,
    Points
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
[[nodiscard]] constexpr const T ConvertTextureInternalFormat(const GraphicsBackend backend, TextureInternalFormat internalFormat) noexcept 
{
    switch(backend) 
    {
        case GraphicsBackend::OpenGL:
        switch(internalFormat) 
        {
            case TextureInternalFormat::R16F: return GL_R16F; break;
            case TextureInternalFormat::RG: return GL_RG; break;
            case TextureInternalFormat::RG16F: return GL_RG16F; break;
            case TextureInternalFormat::RGB: return GL_RGB; break;
            case TextureInternalFormat::RGB16F: return GL_RGB16F; break;
            case TextureInternalFormat::RGBA: return GL_RGBA; break;
            case TextureInternalFormat::RGBA16F: return GL_RGBA16F; break;
            case TextureInternalFormat::RGBA32F: return GL_RGBA32F; break;
        }
    }
}

template<typename T>
[[nodiscard]] constexpr const T ConvertTextureFormat(const GraphicsBackend backend, TextureFormat format) noexcept 
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