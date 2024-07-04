#ifndef MAMMOTH_2D_GL_VERTEX_INPUT_HPP
#define MAMMOTH_2D_GL_VERTEX_INPUT_HPP

#include "graphics/vertex_input.hpp"

#include <glad/gl.h>


struct VertexInputBlueprint 
{

};

class GLVertexInput : public IVertexInput 
{
public:
    GLVertexInput();

    [[nodiscard]] constexpr const GLuint& GetVertexArray() noexcept { return mVertexArray; }

    

private:
    GLuint mVertexArray;
    GLuint mIndexBuffer;
    GLuint mVertexBuffer;
};



#endif