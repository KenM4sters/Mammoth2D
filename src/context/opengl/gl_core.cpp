#include "gl_core.hpp"

namespace mt 
{

std::string getGLErrorString(GLenum error) 
{
    switch (error) 
    {
        case GL_NO_ERROR:          return "GL_NO_ERROR";
        case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:                   return "Unknown Error";
    }
}


void checkGLError(const char* stmt, const char* file, int line) 
{
    GLenum error = glGetError();

    if (error != GL_NO_ERROR) 
    {
        std::cerr << "OpenGL error in file " << file << " at line " << line << ": " 
                  << getGLErrorString(error) << " (" << error << ") in statement: " << stmt << std::endl;
    }
}

constexpr GLenum convertToGLAddressMode(SamplerAddressMode addressMode) noexcept 
{
    switch(addressMode) 
    {
        case SamplerAddressMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case SamplerAddressMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
        case SamplerAddressMode::Repeat: return GL_REPEAT;
        case SamplerAddressMode::MirroredRepeat: return GL_MIRRORED_REPEAT;
    }    
}

constexpr GLenum convertToGLFilterMode(SamplerFilterMode filterMode) noexcept 
{
    switch(filterMode) 
    {
        case SamplerFilterMode::Nearest: return GL_NEAREST;
        case SamplerFilterMode::Linear: return GL_LINEAR;
    }    
}

constexpr GLenum convertToGLMipMapMode(SamplerMipMapMode mipMapMode) noexcept 
{
    switch(mipMapMode) 
    {
        case SamplerMipMapMode::MipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
        case SamplerMipMapMode::MipMapLinear: return GL_LINEAR_MIPMAP_LINEAR;
    }    
}

constexpr GLenum convertToGLTargetType(TargetType type) noexcept 
{
    switch(type) 
    {
        case TargetType::Texture2D: return GL_TEXTURE_2D; 
        case TargetType::TextureCube: return GL_TEXTURE_CUBE_MAP; 
    }
}


constexpr GLenum convertToGLInternalFormat(InternalFormat internalFormat) noexcept 
{
    switch(internalFormat) 
    {
        case InternalFormat::R32: return GL_R32I;
        case InternalFormat::R32F: return GL_R32F;
        case InternalFormat::RG32: return GL_RG32I;
        case InternalFormat::RG32F: return GL_RG32F;
        case InternalFormat::RGB32: return GL_RGB32I;
        case InternalFormat::RGB32F: return GL_RGB32F;
        case InternalFormat::RGBA32: return GL_RGBA32I;
        case InternalFormat::RGBA32F: return GL_RGBA32F;
        case InternalFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
    }    
}

constexpr GLenum convertToGLFormat(Format format) noexcept 
{
    switch(format) 
    {
        case Format::RG: return GL_RG;
        case Format::RGB: return GL_RGB;
        case Format::RGBA: return GL_RGBA;
        case Format::DepthStencil: return GL_DEPTH_STENCIL;
    }    
}

constexpr GLenum convertToGLValueType(ValueType type) noexcept 
{
    switch(type) 
    {
        case ValueType::UInt: return GL_UNSIGNED_INT;
        case ValueType::SInt: return GL_INT;
        case ValueType::UChar: return GL_UNSIGNED_BYTE;
        case ValueType::SChar: return GL_BYTE;
        case ValueType::Float: return GL_FLOAT;
    }    
}


constexpr GLenum convertToGLAttachmentTarget(Attachment attachment) noexcept 
{
    switch(attachment) 
    {
        case Attachment::Color0: return GL_COLOR_ATTACHMENT0;
        case Attachment::Color1: return GL_COLOR_ATTACHMENT1;
        case Attachment::Color2: return GL_COLOR_ATTACHMENT2;
        case Attachment::Color3: return GL_COLOR_ATTACHMENT3;
        case Attachment::Depth: return GL_DEPTH_ATTACHMENT;
        case Attachment::Stencil: return GL_STENCIL_ATTACHMENT;
        case Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;
    } 
}
}