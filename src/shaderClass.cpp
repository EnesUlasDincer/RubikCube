#include "../include/shaderClass.hpp"
#include <iostream>

unsigned int shaderClass::CompilerShader(unsigned int type, const::std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // &source[0]; 
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TO DO: Erro Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " 
        << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << 
        " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }
    

    return id;
}

unsigned int shaderClass::CreateShader()
{
    program = glCreateProgram();

    unsigned int vs = CompilerShader(GL_VERTEX_SHADER, _vertexShader);
    unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, _fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// Activates the Shader Program
void shaderClass::Activate()
{
	glUseProgram(program);
}

// Deactivates the Shader Program
void shaderClass::Deactivate()
{
	glUseProgram(0);
}

// Deletes the Shader Program
void shaderClass::Delete()
{
	glDeleteProgram(program);
}