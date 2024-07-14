#include "gl_context.hpp"

#include "gl_buffer.hpp"
#include "gl_program.hpp"
#include "gl_texture.hpp"
#include "gl_sampler.hpp"
#include "gl_frame_buffer.hpp"
#include "gl_resource.hpp"
#include "gl_shader.hpp"
#include "gl_vertex_input.hpp"

namespace mt 
{


GLGraphicsContext::~GLGraphicsContext()  
{

}

void GLGraphicsContext::init(const GraphicsSettings& settings) 
{
    m_window = new GLWindow();
    m_window->create(settings.name, settings.pixelViewportWidth, settings.pixelViewportHeight);
}

void GLGraphicsContext::shutdown() 
{
    m_window->destroy();
    delete m_window;
}


Window* GLGraphicsContext::getWindow() const 
{
    return m_window;
}


VertexBuffer* GLGraphicsContext::createVertexBuffer(
    const Memory*       memory, 
    VertexBufferFlags   flags
)  
{
    VertexBuffer* vb = static_cast<VertexBuffer*>(new GLVertexBuffer());
    vb->create(memory, flags);
    return vb;
}

IndexBuffer* GLGraphicsContext::createIndexBuffer(
    const Memory*       memory,
    IndexBufferFlags    flags
)  
{
    IndexBuffer* ib = static_cast<IndexBuffer*>(new GLIndexBuffer());
    ib->create(memory, flags);
    return ib;
}

UniformBuffer* GLGraphicsContext::createUniformBuffer(
    const Memory*       memory, 
    UniformBufferFlags  flags
)  
{
    UniformBuffer* ub = static_cast<UniformBuffer*>(new GLUniformBuffer());
    ub->create(memory, flags);
    return ub;
}

Program* GLGraphicsContext::createProgram(
    const char*         vertPath, 
    const char*         fragPath
)  
{
    Program* p = static_cast<Program*>(new GLProgram());
    p->create(vertPath, fragPath);
    return p;
}

Texture* GLGraphicsContext::createTexture(
    TargetType          target, 
    uint32_t            level, 
    InternalFormat      internalFormat, 
    uint32_t            width,  
    uint32_t            height,  
    Format              format, 
    ValueType           type, 
    uint32_t            nMipMaps, 
    uint32_t            flags, 
    const Sampler*    sampler
)   
{
    Texture* tex = static_cast<Texture*>(new GLTexture());
    tex->create(target, level, internalFormat, width, height, format, type, nMipMaps, flags, sampler);
    return tex;
}

Sampler* GLGraphicsContext::createSampler(
    SamplerAddressMode  addressModeT, 
    SamplerAddressMode  addressModeS, 
    SamplerAddressMode  addressModeU, 
    SamplerFilterMode   minFilter, 
    SamplerFilterMode   magFilter
)  
{
    Sampler* sampler = static_cast<Sampler*>(new GLSampler());
    sampler->create(addressModeS, addressModeT, addressModeU, minFilter, magFilter);
    return sampler;
}

FrameBuffer* GLGraphicsContext::createFrameBuffer(
    const FrameBufferAttachment*   attachments, 
    size_t                         count
)  
{
    FrameBuffer* frameBuffer = static_cast<FrameBuffer*>(new GLFrameBuffer());
    frameBuffer->create(attachments, count);
    return frameBuffer;
}   

Resource* GLGraphicsContext::createResource(
    const char*         name, 
    ResourceType        type, 
    const Memory*       memory
) 
{
    Resource* res = static_cast<Resource*>(new GLResource());
    res->create(name, type, memory);
    return res;
}

Shader* GLGraphicsContext::createShader(
    const Program*      program, 
    Resource*     resources, 
    size_t              count
) 
{
    Shader* shader = static_cast<Shader*>(new GLShader());
    shader->create(program, resources, count);
    return shader;
}

VertexInput* GLGraphicsContext::createVertexInput(
    const VertexBuffer* vbuffer, 
    const VertexLayout* layout, 
    const IndexBuffer*  ibuffer
) 
{
    VertexInput* vinput = static_cast<VertexInput*>(new GLVertexInput());
    vinput->create(vbuffer, layout, ibuffer);
    return vinput;
}




}