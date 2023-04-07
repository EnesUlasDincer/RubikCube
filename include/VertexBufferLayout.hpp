#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <signal.h>



struct VertexBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    bool is_normalization_required;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        if(!(false)) raise(SIGINT);
        return 0;
    }

};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferLayoutElement> elements;
    unsigned int stride;
public:
    VertexBufferLayout(/* args */) : stride(0) {};

    // Determines the attributes of the vertexArray
    void Pushf(unsigned int count, bool _is_normalization_required)
    {
        elements.push_back({GL_FLOAT, count, _is_normalization_required});
        stride += sizeof(GL_FLOAT) * count;
    }
    // Returns the stride value
    unsigned int GetStride() const {return stride;}

    // Returns VertexBufferLayoutElement vector
    const std::vector<VertexBufferLayoutElement> GetElement() const {return elements;}
};
