#ifndef MAMMOTH_2D_GL_RENDERER_HPP
#define MAMMOTH_2D_GL_RENDERER_HPP

#include <iostream>

#define GL_CHECK(stmt) do { \
    stmt; \
    CheckGLError(#stmt, __FILE__, __LINE__); \
} while (0)

class GLRenderer final 
{
public:
    GLRenderer();
    ~GLRenderer();
    
    void Resize(const uint32_t width, const uint32_t height) noexcept;

private:
    
};

#endif