#ifndef MAMMOTH_2D_MAMMOTH_HPP
#define MAMMOTH_2D_MAMMOTH_HPP

#include <glad/gl.h>

#include <iostream>


#define MT_MAX_VERTEX_BUFFERS 100
#define MT_MAX_INDEX_BUFFERS 100
#define MT_MAX_UNIFORM_BUFFERS 100
#define MT_MAX_PROGRAMS 100
#define MT_MAX_TEXTURES 100
#define MT_MAX_SAMPLERS 100
#define MT_MAX_FRAME_BUFFERS 100

#define MT_INVALID_HANDLE UINT16_MAX

#define MT_HANDLE(name)                                             \
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

class Texture;
class Sampler;
class Window;

/**
 * @brief Rendering API of choice. Eventually this will cover OpenGL, Vulka, Metal and DX12,
 * but for now only OpenGL and Vulkan are being supported.
 */
enum class GraphicsBackend 
{
    OpenGL
};

/**
 * @brief
 */
struct GraphicsSettings 
{
    GraphicsBackend backend;
    const char* name;
    uint32_t pixelViewportWidth;
    uint32_t pixelViewportHeight;
};


/**
 * @brief Specifies how the sampler will handle texture coordinates outside of the [0, 1]
 * range.
 */
enum class SamplerAddressMode
{
    Repeat,                 ///< Wraps back around to [0, 1]
    MirroredRepeat,         ///< Same as repeat, but reflects the texture.
    ClampToEdge,            ///< Stretches the texture to the edge (ideal in most situations).
    ClampToBorder           ///< 
};


/**
 * @brief Specifies how the sampler will handle texture coordinates that do not map directly
 * to a texel, which can happen when the image has been scaled. 
 */
enum class SamplerFilterMode 
{
    Nearest,                ///< Selects the closest texel (pixelated look).
    Linear                  ///< Linearly interpolates between relative texels (smooth look).
};


/**
 * @brief Specifies how the sampler will handle texture coordinates that do not map directly
 * to a texel for MipMaps of a texture.
 */
enum class SamplerMipMapMode 
{
    MipMapNearest,          ///< Selects the closest texel (pixelated look).
    MipMapLinear            ///< Linearly interpolates between relative texels (smooth look).
};


/**
 * @brief
 */
enum class TargetType 
{
    Texture2D,
    TextureCube
};


/**
 * @brief 
 */
enum class InternalFormat 
{
    R32,
    R32F,
    RG32,
    RG32F,
    RGB32,
    RGB32F,
    RGBA32,
    RGBA32F,
    Depth24Stencil8
};


/**
 * @brief
 */
enum class Format 
{
    RG,
    RGB,
    RGBA,
    DepthStencil
};


/**
 * @brief Specifies the different types of frame buffer attachments.
 * @note Color0 represents the 1st color attachment.
 */
enum class Attachment 
{
    Color0,
    Color1,
    Color2,
    Color3,
    Depth,
    Stencil,
    DepthStencil
};


/**
 * @brief An exhaustive list of the possible attributes. Names are important to match in DX12 
 * so these enum types act as indexes into an array of strings that correspond to the names
 * in shaders.
 * 
 * You should use these types regardless of the GraphicsBackend for consistency.
 */
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


/**
 * @brief The possible types of a single value within the context of textures and attributes.
 * Often it's important to know whether something is an array of floats, characters or integers.
 */
enum class ValueType 
{
    UInt,
    SInt,
    UChar,
    SChar,
    Float
};


/**
 * @brief
 */
enum class ResourceType 
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



/**
 * @brief Encapsulates a void pointer with a size in bytes often used to map data to buffers.
 */
struct Memory 
{
    void* data;                
    size_t byteSize;
};


/**
 * @brief
 */
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

/**
 * @brief 
 */
struct VertexBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};


/**
 * @brief
 */
struct IndexBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};


/**
 * @brief
 */
struct UniformBufferFlags 
{
    enum Enum 
    {
        Static,
        Dynamic
    };
};


/**
 * @brief
 */
struct FrameBufferAttachment 
{
    Texture* pTexture;
    Attachment attachment;
};


/**
 * @brief 
 */
struct Extent 
{
    uint32_t width;
    uint32_t height;
};

/**
 * @brief 
 */
struct Transform 
{
    float* pModel;
    size_t matrixCount;
};


/**
 * @brief
 */
struct VertexAttribute 
{
    VertexAttribute(Attribute attribute, ValueType type, size_t count)
        : type{type},
        count{count},
        byteOffset{0}
    {
        switch(type) 
        {
            case ValueType::UInt: byteSize = count * 4; break;
            case ValueType::SInt: byteSize = count * 4; break;
            case ValueType::UChar: byteSize = count * 1; break;
            case ValueType::SChar: byteSize = count * 1; break;
            case ValueType::Float: byteSize = count * 4; break;
        }
    }   
    
    ValueType type;
    size_t count;
    size_t byteOffset;
    size_t byteSize;
};


/**
 * @brief 
 */
struct VertexLayout 
{
    explicit VertexLayout(VertexAttribute* attributes, size_t count) noexcept
        : attributes{attributes}, 
        count{count},
        stride{0} 
    {
        for(size_t i = 0; i < count; i++) 
        {
            attributes[i].byteOffset = stride;
            stride += attributes[i].byteSize;
        }   
    }

    VertexAttribute* attributes;
    size_t count;
    size_t stride;
};


/**
 * @brief
 */
class VertexBuffer 
{   
    friend class GLVertexBuffer;
public:
    VertexBuffer(const VertexBuffer& other) = delete;
    VertexBuffer& operator=(const VertexBuffer& other) = delete;

    virtual void create(const Memory* memory, VertexBufferFlags flags) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

    virtual ~VertexBuffer() {}
    
private:
    explicit VertexBuffer() noexcept = default;

};


/**
 * @brief
 */
class IndexBuffer 
{
    friend class GLIndexBuffer;
public:
    IndexBuffer(const IndexBuffer& other) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;

    virtual void create(const Memory* memory, IndexBufferFlags flags) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

    virtual ~IndexBuffer() {}
    
private:
    explicit IndexBuffer() noexcept = default;

};


/**
 * @brief
 */
class UniformBuffer 
{
    friend class GLUniformBuffer;
public:
    UniformBuffer(const UniformBuffer& other) = delete;
    UniformBuffer& operator=(const UniformBuffer& other) = delete;
    UniformBuffer(UniformBuffer&& other) = default;
    UniformBuffer& operator=(UniformBuffer&& other) = default;

    virtual void create(const Memory* memory, UniformBufferFlags flags) = 0;

    virtual void update(const Memory* memory, size_t byteOffset) = 0;

    virtual void destroy() = 0;

    virtual ~UniformBuffer() {}
    
private:
    explicit UniformBuffer() noexcept = default;

};


/**
 * @brief
 */
class Program 
{
    friend class GLProgram;
public:
    Program(const Program& other) = delete;
    Program& operator=(const Program& other) = delete;

    virtual void create(const char* vertPath, const char* fragPath) = 0;

    virtual void destroy() = 0;

    virtual ~Program() {}
    
private:
    explicit Program() noexcept = default;

};


/**
 * @brief
 */
class Texture 
{
    friend class GLTexture;
public: 
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

	virtual void create(
        TargetType target,
        uint32_t level,
        InternalFormat internalFormat,
        uint32_t width, 
        uint32_t height, 
        Format format,
        ValueType type,
        uint32_t nMipMaps,
        uint32_t flags,
        const Sampler* sampler
    ) = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual void destroy() = 0;

    virtual ~Texture() {}
    
private:
    explicit Texture() noexcept = default;

};

/**
 * @brief
 */
class Sampler 
{
    friend class GLSampler;
public: 
    Sampler(const Sampler& other) = delete;
    Sampler& operator=(const Sampler& other) = delete;

    virtual void create(
        SamplerAddressMode addressModeS,
        SamplerAddressMode addressModeT,
        SamplerAddressMode addressModeR,
        SamplerFilterMode minFilter,
        SamplerFilterMode magFilter
    ) = 0;

    virtual void update(
        SamplerAddressMode addressModeS,
        SamplerAddressMode addressModeT,
        SamplerAddressMode addressModeR,
        SamplerFilterMode minFilter,
        SamplerFilterMode magFilter
    ) = 0;

    virtual void detroy() = 0;

    virtual ~Sampler() {}
    
private:
    explicit Sampler() noexcept = default;

};



/**
 * @brief
 */
class FrameBuffer
{
    friend class GLFrameBuffer;
public:
    FrameBuffer(const FrameBuffer& other) = delete;
    FrameBuffer& operator=(const FrameBuffer& other) = delete;

    virtual void create(const FrameBufferAttachment* attachements, size_t count) = 0;

    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual void destroy() = 0;

    virtual ~FrameBuffer() {}
    
private:
    explicit FrameBuffer() noexcept = default;

};


/**
 * @brief
 */
class Resource 
{
    friend class GLResource;
public:
    Resource(const Resource& other) = delete;
    Resource& operator=(const Resource& other) = delete;
    Resource(Resource&& other) = default;
    Resource& operator=(Resource&& other) = default;

    virtual void create(const char* name, ResourceType type, const Memory* memory) = 0;

    virtual void update(const Memory* memory) = 0;

    virtual void destroy() = 0;

    virtual ~Resource() {}
    
private:
    explicit Resource() noexcept = default;

};


/**
 * @brief
 */
class Shader   
{
    friend class GLShader;
public: 
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    virtual void create(const Program* program, Resource* resources, size_t count) = 0;

    virtual void update(std::string name, const Memory* memory) = 0;

    virtual void destroy() = 0;

    virtual ~Shader() {} 
    
private:
    explicit Shader() noexcept = default;

};


/**
 * @brief
 */
class VertexInput 
{
    friend class GLVertexInput;
public:
    VertexInput(const VertexInput& other) = delete;
    VertexInput& operator=(const VertexInput& other) = delete;

    virtual void create(const VertexBuffer* buffer, const VertexLayout* layout, const IndexBuffer* indexBuffer) = 0;

    virtual void destroy() = 0;

    virtual ~VertexInput() {}
    
private:
    explicit VertexInput() noexcept = default;

};


/**
 * @brief
 */
void init(
    const GraphicsSettings& config
);


/**
 * @brief
 */
void shutdown();


/**
 * @brief
 */
[[nodiscard]] Window* getWindow();


/**
 * @brief
 */
[[nodiscard]] VertexBuffer* createVertexBuffer(
    const Memory*       memory, 
    VertexBufferFlags   flags
);


/**
 * @brief
 */
[[nodiscard]] IndexBuffer* createIndexBuffer(
    const Memory*       memory, 
    IndexBufferFlags    flags
);


/**
 * @brief
 */
[[nodiscard]] UniformBuffer* createUniformBuffer(
    const Memory*       memory,
    UniformBufferFlags  flags
);


/**
 * @brief
 */
[[nodiscard]] Program* createProgram(
    const char*         vertPath,
    const char*         fragPath
);


/**
 * @brief
 */
[[nodiscard]] Texture* createTexture(
    TargetType          target,  
    uint32_t            level, 
    InternalFormat      internalFormat,  
    uint32_t            width,     
    uint32_t            height,    
    Format              format,  
    ValueType           type, 
    uint32_t            nMipMaps,  
    uint32_t            flags, 
    const Sampler*      sampler  
);


/**
 * @brief
 */
[[nodiscard]] Sampler* createSampler(
    SamplerAddressMode         addressModeS,
    SamplerAddressMode         addressModeT,
    SamplerAddressMode         addressModeR,
    SamplerFilterMode          minFilter,
    SamplerFilterMode          magFilter
);


/**
 * @brief
 */
[[nodiscard]] FrameBuffer* createFrameBuffer(
    const FrameBufferAttachment*   attachments,
    size_t                         count
);


/**
 * @brief
 */
[[nodiscard]] Resource* createResource(
    const char*         name,
    ResourceType        type,
    const Memory*       memory
);


/**
 * @brief
 */
[[nodiscard]] Shader* createShader(
    const Program*      program,
    Resource*     resources,
    size_t              count
);


/**
 * @brief
 */
[[nodiscard]] VertexInput* createVertexInput(
    const VertexBuffer* vBuffer,
    const VertexLayout* layout,
    const IndexBuffer* iBuffer
);


/**
 * @brief
 */
void submit(
    const VertexInput*  input, 
    const Shader*       shader
);



}


#endif