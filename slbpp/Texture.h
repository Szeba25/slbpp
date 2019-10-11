#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "stb_image.h"

class Texture {
private:
	std::string fileName;
	GLuint textureID;
public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void bind();
};
