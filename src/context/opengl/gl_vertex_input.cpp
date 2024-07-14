#include "gl_vertex_input.hpp"


namespace mt 
{

void GLVertexInput::create(const VertexBuffer* vbuffer, const VertexLayout* layout, const IndexBuffer* ibuffer) 
{

    const GLVertexBuffer* vbo = static_cast<const GLVertexBuffer*>(vbuffer);
    const GLIndexBuffer* ebo = static_cast<const GLIndexBuffer*>(ibuffer);

    GL_CHECK(glGenVertexArrays(1, &m_vao));

    GL_CHECK(glBindVertexArray(m_vao));
    
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo->GetGLHandle()));

    if(ebo)
    {
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->GetGLHandle()));
    }

    for(size_t i = 0; i < layout->count; i++) 
    {
        const auto& attrib = layout->attributes[i];

        GL_CHECK(glVertexAttribPointer(i, attrib.count, GL_FLOAT, GL_FALSE, layout->stride, (void*)attrib.byteOffset));
        GL_CHECK(glEnableVertexAttribArray(i));
    }

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void GLVertexInput::destroy() 
{
    glBindVertexArray(GL_NONE);
    glDeleteVertexArrays(1, &m_vao);
}

}