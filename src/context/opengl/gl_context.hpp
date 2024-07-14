#ifndef MAMMOTH_2D_GL_CONTEXT_HPP
#define MAMMOTH_2D_GL_CONTEXT_HPP


#include "context/common/context.hpp"
#include "window/gl_window.hpp"


namespace mt 
{

class GLGraphicsContext final : public IGraphicsContext 
{
public:
    explicit GLGraphicsContext() noexcept
        : m_window{nullptr}
    {}

    virtual ~GLGraphicsContext();

    virtual void init(const GraphicsSettings& settings) override;

    virtual void shutdown() override;

    [[nodiscard]] virtual Window* getWindow() const override;

    [[nodiscard]] virtual VertexBuffer* createVertexBuffer(const Memory* memory, VertexBufferFlags flags) override;

    [[nodiscard]] virtual IndexBuffer* createIndexBuffer(const Memory* memory, IndexBufferFlags flags) override;

    [[nodiscard]] virtual UniformBuffer* createUniformBuffer(const Memory* memory, UniformBufferFlags flags) override;

    [[nodiscard]] virtual Program* createProgram(const char* vertPath, const char* fragPath) override;

    [[nodiscard]] virtual Texture* createTexture(TargetType target, uint32_t level, InternalFormat internalFormat, uint32_t width, uint32_t height, Format format, ValueType type, uint32_t nMipMaps, uint32_t flags, const Sampler* sampler) override;

    [[nodiscard]] virtual Sampler* createSampler(SamplerAddressMode addressModeS, SamplerAddressMode addressModeT, SamplerAddressMode addressModeU, SamplerFilterMode minFilter, SamplerFilterMode magFilter) override;

    [[nodiscard]] virtual FrameBuffer* createFrameBuffer(const FrameBufferAttachment* attachments, size_t count) override;

    [[nodiscard]] virtual Resource* createResource(const char* name, ResourceType type, const Memory* memory) override;
    
    [[nodiscard]] virtual Shader* createShader(const Program* program, Resource* resources, size_t count) override;
    
    [[nodiscard]] virtual VertexInput* createVertexInput(const VertexBuffer* vbuffer, const VertexLayout* layout, const IndexBuffer* ibuffer) override;

private:
    GLWindow* m_window;
};

}

#endif