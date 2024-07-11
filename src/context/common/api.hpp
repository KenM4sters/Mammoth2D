#ifndef MAMMOTH_2D_API_HPP
#define MAMMOTH_2D_API_HPP

#include <glad/gl.h>

#include <vector>

#define MAMMOTH_INVALID_HANDLE UINT16_MAX

#define MAMMOTH_HANDLE(name)                                        \
    struct name                                                     \
    {                                                               \
        uint16_t m_idx;                                             \
        [[nodiscard]] constexpr bool isValid() const noexcept       \
        {                                                           \
            return m_idx != MAMMOTH_INVALID_HANDLE;                 \
        }                                                           \
    };                                                             


namespace mt 
{

MAMMOTH_HANDLE(VertexBufferHandle);
MAMMOTH_HANDLE(IndexBufferHandle);
MAMMOTH_HANDLE(UniformBufferHandle);
MAMMOTH_HANDLE(ProgramHandle);
MAMMOTH_HANDLE(TextureHandle);
MAMMOTH_HANDLE(FramebufferHandle);


class Texture;

enum class GraphicsBackend 
{
    OpenGL,
    Vulkan
};

enum class AddressMode
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

enum class FilterMode 
{
    Nearest,
    Linear,
};

enum class MipMapMode 
{
    MipMapNearest,
    MipMapLinear
};

enum class AttachmentTarget 
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

enum class AttributeFormat 
{
    Float,
    Int,
    Vec2f,
    Vec2i,
    Vec3f,
    Vec3i,
    Vec4f,
    Vec4i, 
};

enum class AttributeType 
{
    Int,
    Float
};

enum class ShaderResourceType 
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

enum class TextureFlags
{
    Read = 1,
    Write = 1 << 1,
    ReadWrite = 1 << 2,
    Color = 1 << 3,
    Depth = 1 << 4,
    Stencil = 1 << 5,
    DepthStencil = 1 << 6,
};


struct BufferView 
{
    size_t byteLength;
    size_t byteOffset;
};

struct BufferAccessor 
{
    BufferAccessor(BufferView* view, size_t byteLength)
        : byteLength{byteLength} 
    {

    }

    size_t byteOffset;
    size_t byteLength;
};

struct BufferLayout 
{
    BufferLayout(BufferAccessor* accessors, size_t byteSize)
        : accessors{accessors}, byteSize{byteSize} 
    {

        if(byteSize % sizeof(BufferAccessor) != 0) 
        {
            // TEMPORARY - trying not to throw errors.
            throw std::runtime_error("Failed to create BufferLayout: byteSize must be a multiple of the size of a BufferAccessor!");
        }

        size_t length = byteSize / sizeof(BufferAccessor);

        size_t stride = 0;
        for(size_t i = 0; i < length; i++) 
        {
            accessors[i].byteOffset = stride;
            stride += accessors[i].byteLength;
        }   
    }

    BufferAccessor* accessors;
    size_t byteSize;
};

struct TextureBlueprint 
{
    AttachmentTarget dimension;
    InternalFormat internalFormat;
    uint32_t width;
    uint32_t height;
    Format format;
    ShaderResourceType type;
    const char* data;
};

struct SamplerBlueprint 
{
    AddressMode sWrap;
    AddressMode tWrap;
    AddressMode rWrap;
    FilterMode min;
    FilterMode mag;
};

}


#endif