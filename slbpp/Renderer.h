#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void clear();
	void resize(int width, int height);
};

