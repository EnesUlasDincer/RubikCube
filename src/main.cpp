#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <string.h>

#include <math.h>
#include "../include/ElementBuffer.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/VertexBufferLayout.hpp"
#include "../include/VertexArray.hpp"
#include "../include/shaderClass.hpp"
#include "../include/renderFunctions.hpp"
#include "../include/Texture.hpp"
#include "../include/Camera.hpp"
#include "../include/Cube.hpp"
#include "../include/MouseProperties.hpp"
#include "../include/KeyProperties.hpp"


// To take jpg image
#include "../include/std_image.h"

#include "vertexShader.glsl"
#include "fragmantShader.glsl"


const float cubeLen = 0.6;

// This variable is defined in MouseProperties.hpp as a EXTERN
MouseProperties mouseProperties_extern;
// This variable is defined in KeyProperties.hpp as a EXTERN
KeyProperties keyProperties_extern;

int main(void)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
    // Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Rubik's Cube", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		COUT << "Failed to create GLFW window" << ENDL;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
    
    // glfwSwapInterval(1); // It is related fps

    if (glewInit() != GLEW_OK)
    {
        COUT << "Erroe in glew!" << ENDL;
    }

    // Enable double buffering
    glfwSwapInterval(1);

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

    // For the cube
    shaderClass shader_cube(textureShader_VR, fragmentShader);
    // Camera initilaziton
	Camera camera(800, 800, glm::vec3(3.0f, 3.0f, 3.0f));

    glEnable(GL_DEPTH_TEST);

    // Game entrance
    info();

    Cube Cube(cubeLen);
    Cube.Init(textureShader_VR, fragmentShader);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
        // Take care of the mouse and keyword presses
        processInput(window);
        //
        framebuffer_editor(window);
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handles camera inputs
		camera.Inputs(window);
		
        // Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, Cube.GetShader(), "camMatrix");

        // Motion start
        Cube.Motion(camera.GetCameraView(),camera.GetView(),camera.GetProjection(),window, mouseProperties_extern, keyProperties_extern);
 
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();


    return 0;
}
