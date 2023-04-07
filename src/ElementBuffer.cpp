#include "../include/ElementBuffer.hpp"


ElementBuffer::ElementBuffer(const void* indices, unsigned int size)
{
    glGenBuffers(1, &ebo);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    count = size/sizeof(unsigned int);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &ebo);
}

void ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void ElementBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
