#pragma once
#include <GL/glew.h>

class ElementBuffer
{
private:
    unsigned int ebo;
    unsigned int count;
public:
    ElementBuffer(const void* indices, unsigned int size);
    ~ElementBuffer();
    // Bind the buffer
    void Bind() const;
    // Unbind the buffer
    void UnBind() const;
    // Return the number of incides
    const unsigned int GetCount() const {return count; }
};
