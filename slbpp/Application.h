#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Input.h"
#include "Renderer.h"

class Application {
private:
	GLFWwindow* window;
	
	Input* input;
	Renderer* renderer;
public:
	Application(GLFWwindow* window);
	virtual ~Application();

	void run();
	void framebufferSizeCallback(int width, int height);
};

