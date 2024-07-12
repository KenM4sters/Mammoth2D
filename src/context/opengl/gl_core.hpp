#ifndef MAMMOTH_2D_GL_CORE_HPP
#define MAMMOTH_2D_GL_CORE_HPP


#include <mammoth/mamoth.hpp>

#include <glad/gl.h>
#include <string>
#include <iostream>

#define GL_CHECK(stmt) do { \
    stmt; \
    checkGLError(#stmt, __FILE__, __LINE__); \
} while (0)



namespace mt 
{
    
std::string getGLErrorString(GLenum error);

void checkGLError(const char* stmt, const char* file, int line);

[[nodiscard]] constexpr GLenum convertToGLTopology(Topology topolgy) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAddressMode(AddressMode addressMode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLFilterMode(FilterMode filterMode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLMipMapMode(MipMapMode mipMapMode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAttachmentTarget(AttachmentTarget attachmentTarget) noexcept;

[[nodiscard]] constexpr GLenum convertToGLInternalFormat(InternalFormat internalFormat) noexcept;

[[nodiscard]] constexpr GLenum convertToGLFormat(Format format) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAttribute(Attribute attribute) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAttributeFormat(AttributeFormat attributeFormat) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAttributeType(AttributeType attributeType) noexcept;

[[nodiscard]] constexpr GLenum convertToGLShaderResourceType(ResourceType ResourceType) noexcept;

[[nodiscard]] constexpr GLenum convertToGLDrawMode(DrawMode drawMode) noexcept;

}




#endif