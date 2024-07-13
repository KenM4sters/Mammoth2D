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

[[nodiscard]] constexpr GLenum convertToGLTargetType(TargetType type) noexcept;

[[nodiscard]] constexpr GLenum convertToGLValueType(ValueType type) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAddressMode(SamplerAddressMode mode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLFilterMode(SamplerFilterMode mode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLMipMapMode(SamplerMipMapMode mode) noexcept;

[[nodiscard]] constexpr GLenum convertToGLAttachmentTarget(Attachment attachment) noexcept;

[[nodiscard]] constexpr GLenum convertToGLInternalFormat(InternalFormat format) noexcept;

[[nodiscard]] constexpr GLenum convertToGLFormat(Format format) noexcept;

}




#endif