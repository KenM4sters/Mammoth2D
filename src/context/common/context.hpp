#ifndef MAMMOTH_2D_GRAPHICS_CONTEXT_HPP
#define MAMMOTH_2D_GRAPHICS_CONTEXT_HPP


#include <mammoth/mamoth.hpp>




namespace mt 
{

class IGraphicsContext 
{
public:
    explicit IGraphicsContext() noexcept {}

    virtual ~IGraphicsContext() = 0;

    IGraphicsContext(const IGraphicsContext& other) = delete;
    IGraphicsContext& operator=(const IGraphicsContext& other) = delete;

    [[nodiscard]] virtual VertexBuffer* createVertexBuffer(const Memory* memory, VertexBufferFlags flags) = 0;

    [[nodiscard]] virtual IndexBuffer* createIndexBuffer(const Memory* memory, IndexBufferFlags flags) = 0;

    [[nodiscard]] virtual UniformBuffer* createUniformBuffer(const Memory* memory, UniformBufferFlags flags) = 0;

    [[nodiscard]] virtual Program* createProgram(const char* vertPath, const char* fragPath) = 0;

    [[nodiscard]] virtual Texture* createTexture(TargetType target, uint32_t level, InternalFormat internalFormat, uint32_t width, uint32_t height, Format format, ValueType type, uint32_t nMipMaps, uint32_t flags, const Sampler* sampler) = 0;

    [[nodiscard]] virtual Sampler* createSampler(SamplerAddressMode addressModeS, SamplerAddressMode addressModeT, SamplerAddressMode addressModeU, SamplerFilterMode minFilter, SamplerFilterMode magFilter) = 0;

    [[nodiscard]] virtual FrameBuffer* createFrameBuffer(const FrameBufferAttachment* attachments, size_t count) = 0;

    [[nodiscard]] virtual Resource* createResource(const char* name, ResourceType type, const Memory* memory) = 0;
    
    [[nodiscard]] virtual Shader* createShader(const Program* program, Resource* resources, size_t count) = 0;
    
    [[nodiscard]] virtual VertexInput* createVertexInput(const VertexBuffer* vbuffer, const VertexLayout* layout, const IndexBuffer* ibuffer) = 0;
    
};

};

#endif
