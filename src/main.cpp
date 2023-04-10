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
#include "../include/BouncingBall.hpp"
#include "../include/Texture.hpp"
#include "../include/Camera.hpp"
#include "../include/Cube.hpp"

// To take jpg image
#include "../include/std_image.h"

#include "vertexShader.glsl"
#include "fragmantShader.glsl"


const float cubeLen = 0.6;
const float cube_center_x = 0.0;
const float cube_center_y = 0.0;
const float cube_center_z = 0.0;
float x_offset = 0.0f;
float y_offset = 0.0f;
float z_offset = 0.0f;
// Vertices coordinates
// GLfloat cube_vertices[] =
// { //     COORDINATES     /        COLORS      /   TexCoord  //
//     // First Cube
// 	cube_center_x - cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z + cubeLen/2,  1.0f, 0.0f, 0.0f, // 0
// 	cube_center_x + cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z + cubeLen/2,  1.0f, 0.0f, 0.0f, // 1
// 	cube_center_x + cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z + cubeLen/2,  1.0f, 0.0f, 0.0f, // 2
// 	cube_center_x - cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z + cubeLen/2,  1.0f, 0.0f, 0.0f, // 3
// 	cube_center_x - cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z - cubeLen/2,  0.0f, 1.0f, 0.0f, // 4
// 	cube_center_x + cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z - cubeLen/2,  0.0f, 1.0f, 0.0f, // 5
// 	cube_center_x + cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z - cubeLen/2,  0.0f, 1.0f, 0.0f, // 6
// 	cube_center_x - cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z - cubeLen/2,  0.0f, 1.0f, 0.0f // 7
//     // Second Cube
// };
GLfloat cube_vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    // First Cube
	cube_center_x - cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z + cubeLen/2, // 0
	cube_center_x + cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z + cubeLen/2, // 1
	cube_center_x + cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z + cubeLen/2, // 2
	cube_center_x - cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z + cubeLen/2, // 3
	cube_center_x - cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z - cubeLen/2, // 4
	cube_center_x + cubeLen/2, cube_center_y - cubeLen/2,  cube_center_z - cubeLen/2, // 5
	cube_center_x + cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z - cubeLen/2, // 6
	cube_center_x - cubeLen/2, cube_center_y + cubeLen/2,  cube_center_z - cubeLen/2  // 7
    // Second Cube
};
// Indices for vertices order
// GLuint cube_indices[] =
// {
// 	0, 1, 2,
// 	0, 2, 3,
	
//     0, 4, 5,
// 	0, 5, 1,

// 	5, 1, 2,
// 	2, 5, 6,

// 	3, 7, 2,
// 	6, 7, 2,

// 	0, 3, 4,
// 	7, 3, 4,

// 	4, 7, 6,
// 	4, 6, 5
// };
GLuint cube_indices[] =
{
	0, 1, 2, 3, // front
	
    0, 4, 5, 1, // down

	5, 1, 2, 6, // right

	3, 7, 6, 2, // up

	0, 3, 7, 4, // left

	4, 7, 6, 5 // back
};




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
	GLFWwindow* window = glfwCreateWindow(800, 800, "BOUNCING BALL", NULL, NULL);
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

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

    // For the cube
    shaderClass shader_cube(textureShader_VR, fragmentShader);

    // Sphere_vertices coordinates
    const int n_point_in_one_cube = 8;
    const int n_faces = 6; 
    const int n_cubes = 27; 


    // shaderClass shaderArray = shaderClass;


    const int vec_count = 3;
    float radius = 0.02f;
    float theta = 0.0f;
    float center_x = -1.0 + radius;
    float center_y =  1.0 - radius;

    int n_point_in_sphere = 4;
    // GLfloat* Sphere_vertices = new GLfloat(n_point_in_sphere * vec_count);
    GLfloat* CUBE_vertices = (GLfloat*)malloc(n_point_in_one_cube * n_faces * n_cubes * vec_count * sizeof(GLfloat));
    for (unsigned int i = 0; i < n_point_in_sphere; i++)
    {

        for (int i = 0; i < n_cubes; i++)
        {
            // cube_0{x}
            x_offset = 2*cubeLen; y_offset = 2*cubeLen; z_offset = 2*cubeLen;
                
	        CUBE_vertices[i * vec_count + 0] = x_offset + cube_center_x - cubeLen/2; // 0 - x
	        CUBE_vertices[i * vec_count + 1] = y_offset + cube_center_y - cubeLen/2; // 0 - y
	        CUBE_vertices[i * vec_count + 2] = z_offset + cube_center_z + cubeLen/2, // 0 - z

	        CUBE_vertices[i * vec_count + 4] = x_offset + cube_center_x + cubeLen/2;
            CUBE_vertices[i * vec_count + 5] = y_offset + cube_center_y - cubeLen/2;
            CUBE_vertices[i * vec_count + 6] = z_offset + cube_center_z + cubeLen/2; // 1

	        CUBE_vertices[i * vec_count + 7] = x_offset + cube_center_x + cubeLen/2;
            CUBE_vertices[i * vec_count + 8] = y_offset + cube_center_y + cubeLen/2;
            CUBE_vertices[i * vec_count + 9] = z_offset + cube_center_z + cubeLen/2; // 2

	        CUBE_vertices[i * vec_count + 10] = x_offset + cube_center_x - cubeLen/2;
            CUBE_vertices[i * vec_count + 11] = y_offset + cube_center_y + cubeLen/2;
            CUBE_vertices[i * vec_count + 12] = z_offset + cube_center_z + cubeLen/2; // 3

	        CUBE_vertices[i * vec_count + 13] = x_offset + cube_center_x - cubeLen/2; 
            CUBE_vertices[i * vec_count + 14] = y_offset + cube_center_y - cubeLen/2;  
            CUBE_vertices[i * vec_count + 15] = z_offset + cube_center_z - cubeLen/2, // 4
	        
            CUBE_vertices[i * vec_count + 16] = x_offset + cube_center_x + cubeLen/2; 
            CUBE_vertices[i * vec_count + 17] = y_offset + cube_center_y - cubeLen/2;  
            CUBE_vertices[i * vec_count + 18] = z_offset + cube_center_z - cubeLen/2, // 5
	        
            CUBE_vertices[i * vec_count + 19] = x_offset + cube_center_x + cubeLen/2; 
            CUBE_vertices[i * vec_count + 20] = y_offset + cube_center_y + cubeLen/2;  
            CUBE_vertices[i * vec_count + 21] = z_offset + cube_center_z - cubeLen/2, // 6
	        
            CUBE_vertices[i * vec_count + 22] = x_offset + cube_center_x - cubeLen/2; 
            CUBE_vertices[i * vec_count + 23] = y_offset + cube_center_y + cubeLen/2;  
            CUBE_vertices[i * vec_count + 24] = z_offset + cube_center_z - cubeLen/2;  // 7
            
        }
        

        CUBE_vertices[i * vec_count]   = cube_center_x + 32;
        CUBE_vertices[i * vec_count+1] = radius * sin(theta) + center_y;
        theta += (360/n_point_in_sphere)*M_PI/180; 
    }

	// Sphere_indices for Sphere_vertices order
    // GLuint* Sphere_indices = new GLuint(n_point_in_sphere);
    GLuint* Sphere_indices = (GLuint*) malloc(n_point_in_sphere * sizeof(GLuint));
    for (unsigned int i = 0; i < n_point_in_sphere; i++)
    {
        Sphere_indices[i] = i;
    }


    // Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
    VertexArray  va_cube;
    va_cube.Config();
    VertexBuffer vb_cube(cube_vertices, sizeof(cube_vertices));
    //ElementBuffer ebo_cube(cube_indices, cubeLenof(cube_indices));

    ElementBuffer ebo_cube_face_0(cube_indices + 0, sizeof(cube_indices)/6);
    ElementBuffer ebo_cube_face_1(cube_indices + 4, sizeof(cube_indices)/6);

    VertexBufferLayout layout_cube;
    layout_cube.Pushf(3,false);
    //layout_cube.Pushf(3,false);
    va_cube.AddBuffer(vb_cube,layout_cube);

    va_cube.UnBind();
    vb_cube.UnBind();
    //ebo_cube.UnBind();
    ebo_cube_face_0.UnBind();
    ebo_cube_face_1.UnBind();


	Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f));


    // Initializes matrices so they are not the null matrix
    glm::mat4 cube_model = glm::mat4(1.0f);
    glm::mat4 cube_cam = glm::mat4(1.0f);

    // Outputs the matrices into the Vertex Shader
    int modelLoc = shader_cube.GetUniformLocation("model");
    //glGetUniformLocation(shader_cube.GetProgram(), "model");
    shader_cube.SetUniformMatrix4f("model", cube_model);
    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube_model));

    int camLoc = glGetUniformLocation(shader_cube.GetProgram(), "camMatrix");
    glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(cube_cam));

    // int vertexColorLocation = glGetUniformLocation(shader_cube.GetProgram(), "uniColor");
    int vertexColorLocation = shader_cube.GetUniformLocation("uniColor");

    glEnable(GL_DEPTH_TEST);

    // Game entrance
    info();
    double prevTime = glfwGetTime();
    float rotation = 0.0f;
    float rotation_x = 0.0f;


    Cube Cube(cubeLen);
    Cube.Init(textureShader_VR, fragmentShader);

    float sinX;
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
		// Tell OpenGL which Shader Program we want to use4
        
        shader_cube.Activate();

        va_cube.Bind();
        //ebo_cube.Bind();

        // Handles camera inputs
		camera.Inputs(window);
		
        // Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shader_cube, "camMatrix");


        //GLCall(glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(cube_cam)));

        glm::mat4 cube_model = glm::mat4(1.0f);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	    {
            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crntTime;
            }
            if(abs(rotation) > 90.0f)
                rotation = 0.0f;
            cube_model = glm::rotate(cube_model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            cube_model = glm::translate(cube_model, glm::vec3( sin(glm::radians(rotation)), 0.0f , -sin(glm::radians(rotation)) ));
	    }else{
            rotation = 0.0f;
            cube_model = glm::rotate(cube_model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	    {
            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation_x += 0.5f;
                prevTime = crntTime;
            }
            if(abs(rotation_x) > 60.0f)
                //rotation_x = 0.0f;
            if(abs(rotation_x) > 89.0f)
                rotation_x = 0.0f;
            sinX = -sin(deg2rad(rotation_x));
            
            cube_model = glm::rotate(cube_model, glm::radians(rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));


            cube_model = glm::translate(cube_model, glm::vec3( 0.0f, (float)sinX , (float)sin(glm::radians(rotation_x)) ));
            
            glm::vec3 base = glm::vec3(0.0f, -0.6f, 0.0f);
            float Rx = 0.0f;
            float Ry = cube_vertices[0];
            float Rz = 0.0f;

	    }else{
            rotation_x = 0.0f;
            cube_model = glm::translate(cube_model, glm::vec3( 0.0f, -sin(glm::radians(rotation_x)) , sin(glm::radians(rotation_x)) ));
            cube_model = glm::rotate(cube_model, glm::radians(rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        // GLCall(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube_model)));
        shader_cube.SetUniformMatrix4f("model",cube_model);
        
        ebo_cube_face_0.Bind();
        // shader_cube.SetUniform4f("uniColor",1.0f, 0.0f, 0.0f, 1.0f);
        
        shader_cube.SetUniform4f("uniColor",RED_COLOR_CODE);
        // glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLE_FAN, ebo_cube_face_0.GetCount(), GL_UNSIGNED_INT, 0));
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
        glLineWidth((GLfloat)10);
        GLCall(glDrawElements(GL_LINE_LOOP, ebo_cube_face_0.GetCount(), GL_UNSIGNED_INT, 0));
        ebo_cube_face_0.UnBind();
        
        ebo_cube_face_1.Bind();
        shader_cube.SetUniform4f("uniColor",0.0f, 1.0f, 0.0f, 1.0f);
        // glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLE_FAN, ebo_cube_face_1.GetCount(), GL_UNSIGNED_INT, 0));
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
        glLineWidth((GLfloat)10);
        GLCall(glDrawElements(GL_LINE_LOOP, ebo_cube_face_1.GetCount(), GL_UNSIGNED_INT, 0));
        ebo_cube_face_1.UnBind();
        va_cube.UnBind();
        shader_cube.Deactivate();

        Cube.SelectSmallCube(camera.GetCameraView(),camera.GetView(),camera.GetProjection(),window);
        Cube.Draw(camera.GetCameraView(), window, prevTime);
        
        //display(window, ball, shader_01.GetProgram() ,_array, _array_ele);,

        // Display the texture
        //dispTexture(window, textureObj, shader_text, va_text, ebo_text);
 
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
