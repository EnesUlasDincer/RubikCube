#pragma once
#include <GL/glew.h>
#include <iostream>
#include "shaderClass.hpp"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(std::string& image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(shaderClass& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

