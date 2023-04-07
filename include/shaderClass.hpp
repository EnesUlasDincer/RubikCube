#pragma once
#include <GL/glew.h>
#include <string>

/*
Usage

    shaderClass shader(vertexShader, fragmentShader);
    shader.Activate();
*/

class shaderClass
{
private:
    const::std::string _vertexShader, _fragmentShader;
    unsigned int program;
public:
    // Constructor
    // Takes the vertexshader and fragmentshader inputs
    shaderClass(const::std::string& vertexShader, const::std::string& fragmentShader) : 
    _vertexShader(vertexShader), _fragmentShader(fragmentShader){CreateShader();};
    ~shaderClass() {Delete();};
    
    // Create a shader 
    unsigned int CreateShader();
    unsigned int CompilerShader(unsigned int type, const::std::string& source);

    // Returns the shader
    unsigned int GetProgram() const {return program;}; 

    // Activates the Shader Program
	void Activate();
    // Deactivates the Shader Program
	void Deactivate();
	// Deletes the Shader Program
	void Delete();
};
