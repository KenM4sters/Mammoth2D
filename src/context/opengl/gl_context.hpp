#ifndef MAMMOTH_2D_GL_CONTEXT_HPP
#define MAMMOTH_2D_GL_CONTEXT_HPP


#include "context.hpp"





namespace mt 
{

class GLGraphicsContext final : public IGraphicsContext 
{
public:
    explicit GLGraphicsContext() noexcept;

    virtual ~GLGraphicsContext() override;

    [[nodiscard]] virtual VertexBuffer* createVertexBuffer(const Memory* memory, VertexBufferFlags flags) override;

    [[nodiscard]] virtual IndexBuffer* createIndexBuffer(const Memory* memory, IndexBufferFlags flags) override;

    [[nodiscard]] virtual UniformBuffer* createUniformBuffer(const Memory* memory, UniformBufferFlags flags) override;

    [[nodiscard]] virtual Program* createProgram(const char* vertPath, const char* fragPath) override;

    [[nodiscard]] virtual Texture* createTexture(uint32_t width, uint32_t height, TextureFlags flags) override;

    [[nodiscard]] virtual Sampler* createSampler(AddressMode adressModeS, AddressMode adressModeT, AddressMode adressModeU, FilterMode minFilter, FilterMode magFilter) override;

    [[nodisacrd]] virtual FrameBuffer* createFrameBuffer(const Attachment* attachments, size_t count) override;


private:

};

}

#endif