#pragma once
#include <GL/glew.h>

class VertexBuffer
{
private:
    unsigned int vbo;
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(){};
    ~VertexBuffer(){glDeleteBuffers(1, &vbo);};

    // Configure the buffer
    void Config(const void* data, unsigned int size);
    // Bind the buffer
    void Bind() const;
    // Unbind the buffer
    void UnBind() const;

};

