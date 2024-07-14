#include <mammoth/mamoth.hpp>

#include "context/common/context.hpp"
#include "context/opengl/gl_context.hpp"

namespace mt 
{

static IGraphicsContext* s_ctx = nullptr;

void init(const GraphicsSettings& settings) 
{
    switch(settings.backend) 
    {
        case GraphicsBackend::OpenGL: s_ctx = static_cast<GLGraphicsContext*>(new GLGraphicsContext());
    }

    s_ctx->init(settings);
}

void shutdown() 
{
    s_ctx->shutdown();
    delete s_ctx;
}

Window* getWindow()
{
    return s_ctx->getWindow();
}

VertexBuffer* createVertexBuffer(
    const Memory*       memory, 
    VertexBufferFlags   flags
) 
{
    return s_ctx->createVertexBuffer(memory, flags);
}

IndexBuffer* createIndexBuffer(
    const Memory*       memory, 
    IndexBufferFlags    flags
) 
{
    return s_ctx->createIndexBuffer(memory, flags);
}


UniformBuffer* createUniformBuffer(
    const Memory*       memory,
    UniformBufferFlags  flags
) 
{
    return s_ctx->createUniformBuffer(memory, flags);
}


Program* createProgram(
    const char*         vertPath,
    const char*         fragPath
) 
{
    return s_ctx->createProgram(vertPath, fragPath);
}


Texture* createTexture(
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
) 
{
    return s_ctx->createTexture(target, level, internalFormat, width, height, 
        format, type, nMipMaps, flags, sampler);
}


Sampler* createSampler(
    SamplerAddressMode         addressModeS,
    SamplerAddressMode         addressModeT,
    SamplerAddressMode         addressModeR,
    SamplerFilterMode          minFilter,
    SamplerFilterMode          magFilter
) 
{
    return s_ctx->createSampler(addressModeS, addressModeT, addressModeR, minFilter, magFilter);
}


FrameBuffer* createFrameBuffer(
    const FrameBufferAttachment*   attachments,
    size_t                         count
) 
{
    return s_ctx->createFrameBuffer(attachments, count);
}


Resource* createResource(
    const char*         name,
    ResourceType        type,
    const Memory*       memory
) 
{
    return s_ctx->createResource(name, type, memory);
}


Shader* createShader(
    const Program*      program,
    Resource*     resources,
    size_t              count
) 
{
    return s_ctx->createShader(program, resources, count);
}


VertexInput* createVertexInput(
    const VertexBuffer* vBuffer,
    const VertexLayout* layout,
    const IndexBuffer* iBuffer
) 
{
    return s_ctx->createVertexInput(vBuffer, layout, iBuffer);
}


void submit(
    const VertexInput*  input, 
    const Shader*       shader
) 
{

}



}