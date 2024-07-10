#ifndef MAMMOTH_2D_API_HPP
#define MAMMOTH_2D_API_HPP

#include <glad/gl.h>

#include <vector>



namespace mt 
{

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

struct RenderTargetBlueprint
{   
    Texture* colorAttachement;
    Texture* depthStencilAttachment;
};

struct ShaderResource 
{
    const char* name;
    ShaderResourceType type;
    void* data;
};

struct ShaderBlueprint 
{
    std::vector<char> vertCode;
    std::vector<char> fragCode; 
    std::vector<Attribute> attributes;
    std::vector<ShaderResource> resources;
};

struct MeshBlueprint 
{
    ShaderBlueprint shaderBlueprint;
    std::vector<float> vertices;

};




}


#endif