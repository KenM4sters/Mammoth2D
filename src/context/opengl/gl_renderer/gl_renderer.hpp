#ifndef MAMMOTH_2D_GL_RENDERER_HPP
#define MAMMOTH_2D_GL_RENDERER_HPP

#include <iostream>

class GLRenderer final 
{
public:
    GLRenderer();
    ~GLRenderer();
    
    void Resize(const uint32_t width, const uint32_t height) noexcept;

private:
    
};

#endif