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
    m_window = std::make_unique<GLWindow>();
    m_window->create(settings.name, settings.pixelViewportWidth, settings.pixelViewportHeight);
}

void GLGraphicsContext::shutdown() 
{
    m_window->destroy();
}


WindowHandle& GLGraphicsContext::getWindow()  
{
    return m_window;
}


VertexBufferHandle GLGraphicsContext::createVertexBuffer(
    const Memory*       memory, 
    uint32_t   flags
)  
{
    std::unique_ptr<GLVertexBuffer> vb = std::make_unique<GLVertexBuffer>();
    vb->create(memory, flags);
    return std::move(vb);
}

IndexBufferHandle GLGraphicsContext::createIndexBuffer(
    const Memory*       memory,
    uint32_t    flags
)  
{
    std::unique_ptr<GLIndexBuffer> ib = std::make_unique<GLIndexBuffer>();
    ib->create(memory, flags);
    return std::move(ib);
}

UniformBufferHandle GLGraphicsContext::createUniformBuffer(
    const Memory*       memory, 
    uint32_t  flags
)  
{
    std::unique_ptr<GLUniformBuffer> ub = std::make_unique<GLUniformBuffer>();
    ub->create(memory, flags);
    return std::move(ub);
}

ProgramHandle GLGraphicsContext::createProgram(
    const char*         vertPath, 
    const char*         fragPath
)  
{
    std::unique_ptr<GLProgram> program = std::make_unique<GLProgram>();
    program->create(vertPath, fragPath);
    return std::move(program);
}

TextureHandle GLGraphicsContext::createTexture(
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
    std::unique_ptr<GLTexture> tex = std::make_unique<GLTexture>();
    tex->create(target, level, internalFormat, width, height, format, type, nMipMaps, flags, sampler);
    return std::move(tex);
}

SamplerHandle GLGraphicsContext::createSampler(
    SamplerAddressMode  addressModeT, 
    SamplerAddressMode  addressModeS, 
    SamplerAddressMode  addressModeU, 
    SamplerFilterMode   minFilter, 
    SamplerFilterMode   magFilter
)  
{
    std::unique_ptr<GLSampler> sampler = std::make_unique<GLSampler>(); 
    sampler->create(addressModeS, addressModeT, addressModeU, minFilter, magFilter);
    return std::move(sampler);
}

FrameBufferHandle GLGraphicsContext::createFrameBuffer(
    const FrameBufferAttachment*   attachments, 
    size_t                         count
)  
{
    std::unique_ptr<GLFrameBuffer> frameBuffer = std::make_unique<GLFrameBuffer>(); 
    frameBuffer->create(attachments, count);
    return std::move(frameBuffer);
}   

ResourceHandle GLGraphicsContext::createResource(
    const char*         name, 
    ResourceType        type, 
    const Memory*       memory
) 
{
    std::unique_ptr<GLResource> res = std::make_unique<GLResource>(); 
    res->create(name, type, memory);
    return std::move(res);
}

ShaderHandle GLGraphicsContext::createShader(
    const Program*      program, 
    Resource*           resources, 
    size_t              count
) 
{
    std::unique_ptr<GLShader> shader = std::make_unique<GLShader>(); 
    shader->create(program, resources, count);
    return std::move(shader);
}

VertexInputHandle GLGraphicsContext::createVertexInput(
    const VertexBuffer* vbuffer, 
    const VertexLayout* layout, 
    const IndexBuffer*  ibuffer
) 
{
    std::unique_ptr<GLVertexInput> vinput = std::make_unique<GLVertexInput>(); 
    vinput->create(vbuffer, layout, ibuffer);
    return std::move(vinput);
}


void GLGraphicsContext::begin(const FrameBuffer* frameBuffer) 
{

}

void GLGraphicsContext::end() 
{

}

void GLGraphicsContext::submit(const VertexInput* vInput, const Shader* shader) 
{
    const GLVertexInput* glVertexInput = static_cast<const GLVertexInput*>(vInput);
    const GLShader* glShader = static_cast<const GLShader*>(shader);

    GL_CHECK(glUseProgram(glShader->getProgram().getGLHandle()));
    GL_CHECK(glBindVertexArray(glVertexInput->getGLHandle()));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    GL_CHECK(glUseProgram(0));
    GL_CHECK(glBindVertexArray(0));
}





}