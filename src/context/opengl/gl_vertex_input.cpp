#include "gl_vertex_input.hpp"


namespace mt 
{

void GLVertexInput::create(const VertexBuffer* vbuffer, const VertexLayout* layout, const IndexBuffer* ibuffer) 
{

    const GLVertexBuffer* vbo = static_cast<const GLVertexBuffer*>(vbuffer);
    const GLIndexBuffer* ebo = static_cast<const GLIndexBuffer*>(ibuffer);

    GL_CHECK(glGenVertexArrays(1, &m_vao));

    glBindVertexArray(m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo->GetGLHandle());
    if(ebo)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->GetGLHandle());
    }

    for(size_t i = 0; i < layout->count; i++) 
    {
        const auto& attrib = layout->attributes[i];

        glVertexAttribPointer(i, attrib.count, GL_FLOAT, GL_FALSE, layout->stride, (void*)attrib.byteOffset);
        glEnableVertexAttribArray(i);
    }

    glBindVertexArray(GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
}

void GLVertexInput::destroy() 
{
    glBindVertexArray(GL_NONE);
    glDeleteVertexArrays(1, &m_vao);
}

}