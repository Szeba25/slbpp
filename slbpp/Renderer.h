#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class Renderer {
private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

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

