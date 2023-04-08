#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <signal.h>



// Matrix operations
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/gtc/matrix_transform.hpp"
#include "../include/glm/glm/gtc/type_ptr.hpp"
#include "../include/glm/glm/gtx/vector_angle.hpp"
#include "../include/glm/glm/gtx/rotate_vector.hpp"

#ifdef _MSC_VER
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(x) if(!(x)) raise(SIGINT)
#endif

void GLClearError();
void GLCheckError();
bool GLLogCall(const char* function, const char* file, int line);

#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

class shaderClass
{
private:
    const::std::string _vertexShader, _fragmentShader;
    unsigned int program;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    // Constructor
    // Takes the vertexshader and fragmentshader inputs
    shaderClass(){};
    shaderClass(const::std::string& vertexShader, const::std::string& fragmentShader) : 
    _vertexShader(vertexShader), _fragmentShader(fragmentShader){CreateShader();};
    ~shaderClass() {Delete();};
    
    // Create a shader 
    unsigned int CreateShader();
    unsigned int CompilerShader(unsigned int type, const::std::string& source);

    // Returns the shader
    unsigned int GetProgram() const {return program;}; 

    // Set the shader program
    void SetProgram(unsigned int _program) {program = _program;}; 

    unsigned int init(const::std::string& vertexShader, const::std::string& fragmentShader);
    // Activates the Shader Program
	void Activate();
    // Deactivates the Shader Program
	void Deactivate();
	// Deletes the Shader Program
	void Delete();

    void SetUniform4f(const::std::string& name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    };

    void SetUniformMatrix4f(const::std::string& name, const glm::mat4& matrix){
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    
    int GetUniformLocation(const::std::string& name);

    shaderClass operator=(shaderClass& obj){
        return obj;
    }

};
