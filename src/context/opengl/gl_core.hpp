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
    
std::string getGLErrorString(GLenum error) noexcept;

void checkGLError(const char* stmt, const char* file, int line);

[[nodiscard]] GLenum convertToGLTargetType(TargetType type) noexcept;

[[nodiscard]] GLenum convertToGLValueType(ValueType type) noexcept;

[[nodiscard]] GLenum convertToGLAddressMode(SamplerAddressMode mode) noexcept;

[[nodiscard]] GLenum convertToGLFilterMode(SamplerFilterMode mode) noexcept;

[[nodiscard]] GLenum convertToGLMipMapMode(SamplerMipMapMode mode) noexcept;

[[nodiscard]] GLenum convertToGLAttachmentTarget(Attachment attachment) noexcept;

[[nodiscard]] GLenum convertToGLInternalFormat(InternalFormat format) noexcept;

[[nodiscard]] GLenum convertToGLFormat(Format format) noexcept;

}




#endif