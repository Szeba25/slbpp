#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Input.h"
#include "Renderer.h"

class Application {
private:
	GLFWwindow* window;

	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::nanoseconds delta;
	std::chrono::nanoseconds maxAccumulator;
	std::chrono::nanoseconds accumulator;

	int updatesPerSecond;
	int updateCounter;
	std::chrono::high_resolution_clock::time_point resetTime;

	Input* input;
	Renderer* renderer;

	void update();
	void render();
public:
	Application(GLFWwindow* window);
	virtual ~Application();

	void run();
	void framebufferSizeCallback(int width, int height);
	void keyCallback(int key, int action);
};

