#include "gl_context.hpp"

#include "gl_buffer.hpp"
#include "gl_program.hpp"
#include "gl_texture.hpp"
#include "gl_sampler.hpp"
#include "gl_frame_buffer.hpp"

namespace mt 
{


explicit GLGraphicsContext::GLGraphicsContext() noexcept 
{

}

GLGraphicsContext::~GLGraphicsContext()  
{

}

VertexBuffer* GLGraphicsContext::createVertexBuffer(
    const Memory*       memory, 
    VertexBufferFlags   flags
)  
{
    VertexBuffer* vb = static_cast<VertexBuffer*>(new GLVertexBuffer());
}

IndexBuffer* GLGraphicsContext::createIndexBuffer(
    const Memory*       memory,
    IndexBufferFlags    flags
)  
{

}

UniformBuffer* GLGraphicsContext::createUniformBuffer(
    const Memory*       memory, 
    UniformBufferFlags  flags
)  
{

}

Program* GLGraphicsContext::createProgram(
    const char*         vertPath, 
    const char*         fragPath
)  
{

}

Texture* GLGraphicsContext::createTexture(
    uint32_t            width, 
    uint32_t            height, 
    TextureFlags        flags
)  
{

}

Sampler* GLGraphicsContext::createSampler(
    AddressMode         adressModeS, 
    AddressMode         adressModeT, 
    AddressMode         adressModeU, 
    FilterMode          minFilter, 
    FilterMode          magFilter
)  
{

}

[[nodisacrd]] FrameBuffer* GLGraphicsContext::createFrameBuffer(
    const Attachment*   attachments, 
    size_t              count
)  
{

}


}