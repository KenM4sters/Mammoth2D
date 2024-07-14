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

    [[nodiscard]] virtual WindowHandle& getWindow() override;

    [[nodiscard]] virtual VertexBufferHandle createVertexBuffer(const Memory* memory, uint32_t flags) override;

    [[nodiscard]] virtual IndexBufferHandle createIndexBuffer(const Memory* memory, uint32_t flags) override;

    [[nodiscard]] virtual UniformBufferHandle createUniformBuffer(const Memory* memory, uint32_t flags) override;

    [[nodiscard]] virtual ProgramHandle createProgram(const char* vertPath, const char* fragPath) override;

    [[nodiscard]] virtual TextureHandle createTexture(TargetType target, uint32_t level, InternalFormat internalFormat, uint32_t width, uint32_t height, Format format, ValueType type, uint32_t nMipMaps, uint32_t flags, const Sampler* sampler) override;

    [[nodiscard]] virtual SamplerHandle createSampler(SamplerAddressMode addressModeS, SamplerAddressMode addressModeT, SamplerAddressMode addressModeU, SamplerFilterMode minFilter, SamplerFilterMode magFilter) override;

    [[nodiscard]] virtual FrameBufferHandle createFrameBuffer(const FrameBufferAttachment* attachments, size_t count) override;

    [[nodiscard]] virtual ResourceHandle createResource(const char* name, ResourceType type, const Memory* memory) override;
    
    [[nodiscard]] virtual ShaderHandle createShader(const Program* program, Resource* resources, size_t count) override;
    
    [[nodiscard]] virtual VertexInputHandle createVertexInput(const VertexBuffer* vbuffer, const VertexLayout* layout, const IndexBuffer* ibuffer) override;

    virtual void begin(const FrameBuffer* frameBuffer) override;

    virtual void end() override;

    virtual void submit(const VertexInput* vInput, const Shader* shader) override;

private:
    WindowHandle m_window;
};

}

#endif