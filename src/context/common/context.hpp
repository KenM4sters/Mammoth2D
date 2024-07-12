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

    [[nodiscard]] virtual Texture* createTexture(uint32_t width, uint32_t height, TextureFlags flags) = 0;

    [[nodiscard]] virtual Sampler* createSampler(AddressMode adressModeS, AddressMode adressModeT, AddressMode adressModeU, FilterMode minFilter, FilterMode magFilter) = 0;

    [[nodisacrd]] virtual FrameBuffer* createFrameBuffer(const Attachment* attachments, size_t count) = 0;
    
};

};

#endif
