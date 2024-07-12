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




[[nodiscard]] constexpr GLenum convertToGLTopology(Topology topolgy) noexcept 
{
    switch(topolgy) 
    {
        case Topology::Lines: return GL_LINES;
        case Topology::LinesList: return GL_LINE_STRIP;
        case Topology::Triangles: return GL_TRIANGLES;
        case Topology::TrianglesList: return GL_TRIANGLE_STRIP;
        case Topology::Points: return GL_POINTS;
    }
}

[[nodiscard]] constexpr GLenum convertToGLAddressMode(AddressMode addressMode) noexcept 
{
    switch(addressMode) 
    {
        case AddressMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case AddressMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
        case AddressMode::Repeat: return GL_REPEAT;
        case AddressMode::MirroredRepeat: return GL_MIRRORED_REPEAT;
    }    
}

[[nodiscard]] constexpr GLenum convertToGLFilterMode(FilterMode filterMode) noexcept 
{
    switch(filterMode) 
    {
        case FilterMode::Nearest: return GL_NEAREST;
        case FilterMode::Linear: return GL_LINEAR;
    }    
}

[[nodiscard]] constexpr GLenum convertToGLMipMapMode(MipMapMode mipMapMode) noexcept 
{
    switch(mipMapMode) 
    {
        case MipMapMode::MipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
        case MipMapMode::MipMapLinear: return GL_LINEAR_MIPMAP_LINEAR;
    }    
}

[[nodiscard]] constexpr GLenum convertToGLAttachmentTarget(AttachmentTarget attachmentTarget) noexcept 
{
    switch(attachmentTarget) 
    {
        case AttachmentTarget::Texture2D: return GL_TEXTURE_2D;
        case AttachmentTarget::Texture3D: return GL_TEXTURE_3D;
        case AttachmentTarget::TextureCube: return GL_TEXTURE_CUBE_MAP;
    }    
}

[[nodiscard]] constexpr GLenum convertToGLInternalFormat(InternalFormat internalFormat) noexcept 
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

[[nodiscard]] constexpr GLenum convertToGLFormat(Format format) noexcept 
{
    switch(format) 
    {
        case Format::RG: return GL_RG;
        case Format::RGB: return GL_RGB;
        case Format::RGBA: return GL_RGBA;
        case Format::DepthStencil: return GL_DEPTH_STENCIL;
    }    
}

[[nodiscard]] constexpr GLenum convertToGLAttribute(Attribute attribute) noexcept 
{
    // switch(attribute) 
    // {
    //     case Attribute::Position: return GL_FLOAT_VEC3;
    //     case Attribute::LinesList: return GL_LINE_STRIP;
    //     case Attribute::Triangles: return GL_TRIANGLES;
    //     case Attribute::TrianglesList: return GL_TRIANGLE_STRIP;
    //     case Attribute::Points: return GL_POINTS;
    // }    
}

[[nodiscard]] constexpr GLenum convertToGLAttributeFormat(AttributeFormat attributeFormat) noexcept 
{
    // switch(attributeFormat) 
    // {
    //     case AttributeFormat::Float: return GL_FLOAT;
    //     case AttributeFormat::Int: return GL_INT;
    //     case AttributeFormat::Vec2i: return GL;
    //     case AttributeFormat::Vec2f: return GL_TRIANGLE_STRIP;
    //     case AttributeFormat::Vec3i: return GL_TRIANGLES;
    //     case AttributeFormat::Vec3f: return GL_TRIANGLE_STRIP;
    //     case AttributeFormat::Vec4i: return GL_TRIANGLES;
    //     case AttributeFormat::Vec4f: return GL_TRIANGLE_STRIP;
    // }    
}

[[nodiscard]] constexpr GLenum convertToGLAttributeType(AttributeType attributeType) noexcept 
{
    // switch(attributeType) 
    // {
    //     case Topology::Lines: return GL_LINES;
    //     case Topology::LinesList: return GL_LINE_STRIP;
    //     case Topology::Triangles: return GL_TRIANGLES;
    //     case Topology::TrianglesList: return GL_TRIANGLE_STRIP;
    //     case Topology::Points: return GL_POINTS;
    // }    
}

[[nodiscard]] constexpr GLenum convertToGLShaderResourceType(ResourceType ResourceType) noexcept 
{
    // switch(shaderResourceType) 
    // {
    //     case ShaderResourceType:: return GL_LINES;
    //     case ShaderResourceType::LinesList: return GL_LINE_STRIP;
    //     case ShaderResourceType::Triangles: return GL_TRIANGLES;
    //     case ShaderResourceType::TrianglesList: return GL_TRIANGLE_STRIP;
    //     case ShaderResourceType::Points: return GL_POINTS;
    // }    
}

[[nodiscard]] constexpr GLenum convertToGLDrawMode(DrawMode drawMode) noexcept 
{
    // switch(drawMode) 
    // {
    //     case DrawMode::Arrays: return GL_LINES;
    //     case DrawMode::Indexed: return GL_LINE_STRIP;
    // }    
}


}