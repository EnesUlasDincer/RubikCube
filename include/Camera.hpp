#pragma once

#include <GL/glew.h>
#include<GLFW/glfw3.h>

// Matrix operations
#include "../include/glm/glm/glm.hpp"
#include "../include/glm/glm/gtc/matrix_transform.hpp"
#include "../include/glm/glm/gtc/type_ptr.hpp"
#include "../include/glm/glm/gtx/vector_angle.hpp"
#include "../include/glm/glm/gtx/rotate_vector.hpp"

#include <iostream>

#include"shaderClass.hpp"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// View and Proj matrices
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	// Multiplication of view and proj matrices
	glm::mat4 CameraMatrix = glm::mat4(1.0f);
	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, shaderClass& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
	// Get the Proj*View matrices
	glm::mat4& GetCameraView(){return CameraMatrix;}; 
	// Get the Projection matrice
	glm::mat4& GetProjection(){return projection;}; 
	// Get the View matrice
	glm::mat4& GetView(){return view;}; 
	// Take the current window size
	void GetandSetWindowSize(GLFWwindow* window){glfwGetWindowSize(window, &width, &height);};
};

void printMatrix(const glm::mat4& matrix);
glm::mat4 perspectiveToTransformation(const glm::mat4& projection);
glm::mat4 perspectiveToHomogeneous(float fovy, float aspect, float zNear, float zFar);