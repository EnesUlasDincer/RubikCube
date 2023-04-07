#include "../include/VertexArray.hpp"

VertexArray::VertexArray(/* args */)
{
    GLCall(glGenVertexArrays(1, &vao));
    Bind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(vao);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer& vbo, VertexBufferLayout& layout)
{
    Bind();
    vbo.Bind();
    
    // I need the detailed information about vertices
    // What is the vertex type?
    // How many? (vec2, vec4 ?)
    // Do they require normalization?
    // Also stride and offset would be nice
    std::vector<VertexBufferLayoutElement> elements = layout.GetElement();
    
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        VertexBufferLayoutElement element = elements[i];
        // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
        glVertexAttribPointer(i, element.count, element.type, element.is_normalization_required, layout.GetStride(), (void*)(offset));
        // Enable the Vertex Attribute so that OpenGL knows to use it
        glEnableVertexAttribArray(i);
        offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
    
}
