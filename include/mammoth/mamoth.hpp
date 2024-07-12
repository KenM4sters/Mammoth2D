#ifndef MAMMOTH_2D_MAMMOTH_HPP
#define MAMMOTH_2D_MAMMOTH_HPP

#include <glad/gl.h>

#include <iostream>


#define MAMMOTH_MAX_VERTEX_BUFFERS 100
#define MAMMOTH_MAX_INDEX_BUFFERS 100
#define MAMMOTH_MAX_UNIFORM_BUFFERS 100
#define MAMMOTH_MAX_PROGRAMS 100
#define MAMMOTH_MAX_TEXTURES 100
#define MAMMOTH_MAX_SAMPLERS 100
#define MAMMOTH_MAX_FRAME_BUFFERS 100

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

struct TextureFlags 
{
    enum Enum 
    {
        ReadOnly = 1,
        WriteOnly = 1 >> 1,
        ReadWrite = 1 >> 2,
        Color = 1 >> 3,
        Depth = 1 >> 4,
        Stencil = 1 >> 5,
    };
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

struct Memory 
{
    void* data;
    size_t byteSize;
};

struct VertexBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};

struct IndexBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};

struct UniformBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};

struct AttachmentFlags 
{   
    enum Enum 
    {
        Color = 1,
        Depth = 1 >> 1,
        Stencil = 1 >> 2
    };
};

struct Attachment 
{
    AttachmentFlags flags;
    Texture* pTexture;
};


class VertexBuffer 
{

    friend class GLVertexBuffer;

public:
    VertexBuffer(const VertexBuffer& other) = delete;
    VertexBuffer& operator=(const VertexBuffer& other) = delete;

    virtual void create(const Memory* memory, VertexBufferFlags flags) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

private:
    explicit VertexBuffer() noexcept = default;

    virtual ~VertexBuffer() = 0;
};


class IndexBuffer 
{
public:
    IndexBuffer(const IndexBuffer& other) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;

    virtual void create(const Memory* memory) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

private:
    explicit IndexBuffer() noexcept = default;

    virtual ~IndexBuffer() = 0;
};


class UniformBuffer 
{
public:
    UniformBuffer(const UniformBuffer& other) = delete;
    UniformBuffer& operator=(const UniformBuffer& other) = delete;

    virtual void create(const Memory* memory) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

private:
    explicit UniformBuffer() noexcept = default;

    virtual ~UniformBuffer() = 0;
};

class Program 
{
public:
    Program(const Program& other) = delete;
    Program& operator=(const Program& other) = delete;

    virtual void create(const char* vertPath, const char* fragPath) = 0;

    virtual void destroy() = 0;

private:
    explicit Program() noexcept = default;

    virtual ~Program() = 0;
};



class Texture 
{
public: 
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    virtual void create(
        uint32_t width, 
        uint32_t height, 
        InternalFormat format, 
        TextureFlags flags
    ) = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual void destroy() = 0;

private:
    explicit Texture() noexcept = default;

    virtual ~Texture() = 0;
};


class Sampler 
{
public: 
    Sampler(const Sampler& other) = delete;
    Sampler& operator=(const Sampler& other) = delete;

    virtual void create(
        AddressMode addressModeS,
        AddressMode addressModeT,
        AddressMode addressModeR,
        FilterMode minFilter,
        FilterMode magFilter
    ) = 0;

    virtual void update(
        AddressMode addressModeS,
        AddressMode addressModeT,
        AddressMode addressModeR,
        FilterMode minFilter,
        FilterMode magFilter
    ) = 0;

    virtual void detroy() = 0;

private:
    explicit Sampler() noexcept = default;

    virtual ~Sampler() = 0;
};


class FrameBuffer
{
public:
    FrameBuffer(const FrameBuffer& other) = delete;
    FrameBuffer& operator=(const FrameBuffer& other) = delete;

    virtual void create(Attachment* attachements, size_t count) = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual void destroy() = 0;

private:
    explicit FrameBuffer() noexcept = default;

    virtual ~FrameBuffer() = 0;
};




VertexBuffer* createVertexBuffer(
    const Memory*       memory, 
    VertexBufferFlags   flags
);


IndexBuffer* createIndexBuffer(
    const Memory*       memory, 
    IndexBufferFlags    flags
);

UniformBuffer* createUniformBuffer(
    const Memory*       memory,
    UniformBufferFlags  flags
);








}


#endif