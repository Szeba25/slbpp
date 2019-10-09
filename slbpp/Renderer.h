#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Shader.h"

class Renderer {
private:
	std::unique_ptr<Shader> shader;

	std::vector<float> vertices;
	unsigned int VBO;
	unsigned int VAO;

public:
	Renderer();
	virtual ~Renderer();

	void clear();
	void test();

	void resize(int width, int height);
};

