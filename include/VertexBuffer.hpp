#pragma once
#include <GL/glew.h>

class VertexBuffer
{
private:
    unsigned int vbo;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer(){glDeleteBuffers(1, &vbo);};
    // Bind the buffer
    void Bind() const;
    // Unbind the buffer
    void UnBind() const;

};

