#ifndef MAMMOTH_2D_GL_VERTEX_INPUT_HPP
#define MAMMOTH_2D_GL_VERTEX_INPUT_HPP


#include <mammoth/mamoth.hpp>
#include "gl_core.hpp"
#include "gl_buffer.hpp"

namespace mt 
{

class GLVertexInput final : public VertexInput 
{
public:
    explicit GLVertexInput() noexcept {} 

    virtual void create(const VertexBuffer* buffer, const VertexLayout* layout, const IndexBuffer* indexBuffer) override;

    virtual void destroy() override;

    [[nodiscard]] constexpr GLuint getGLHandle() const { return m_vao; }

private:
    GLuint m_vao;
};


}


#endif