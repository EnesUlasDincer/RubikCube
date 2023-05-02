#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <signal.h>
#include <math.h>

#include "ElementBuffer.hpp"
#include "VertexArray.hpp"
#include "shaderClass.hpp"
#include "Texture.hpp"



#define PRINT_MACROS

#define COUT std::cout
#define ENDL std::endl


#define deg2rad(x) x*M_PI/180


#ifndef SCREEN_SIZE
#define SCREEN_SIZE

const int MAX_SCREEN_WIDTH = 1920;
const int MAX_SCREEN_HEIGHT = 1080; 

#endif

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

#ifndef STATE_MACHINE
#define STATE_MACHINE(Condition, state, output, expected_output_1, expected_output_2) ;\
    switch (state) { ;\
        case 0: if( Condition ) { state = 1; } break; ;\
        case 1: output = expected_output_1; if( !Condition ) { state = 2; } break; ;\
        case 2: if( Condition ) { state = 3; } break; ;\
        case 3: output = expected_output_2; if( !Condition ) { state = 4; } break; ;\
        case 4: if( Condition ) { state = 1; } break; ;\
        default: break; ;\
        } 
#endif


#ifndef PRINT_MACROS
#define PRINT_MACROS

#define COUT std::cout
#define ENDL std::endl

#endif

// Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int heigth);

void framebuffer_editor(GLFWwindow* window);

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window);

void colorChanger(float * ColorChannel, float increment);

// Prints general information about program
void info();
// Prints information about controllers
void infoHelp();

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
