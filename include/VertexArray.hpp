#pragma once
#include <GL/glew.h>
#include "ElementBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "renderFunctions.hpp"


class VertexArray
{
private:
    unsigned int vao;
public:
    VertexArray(bool flag);
    VertexArray(){};
    ~VertexArray(){ glDeleteVertexArrays(1, &vao); };

    // Configure the buffer
    void Config();
    // Bind the buffer
    void Bind() const;
    // Unbind the buffer
    void UnBind() const;
    // Extarcts and links the vertex buffer data into vertexArray
    void AddBuffer(VertexBuffer& vbo, VertexBufferLayout& layout);
};

