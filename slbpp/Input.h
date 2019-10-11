#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

enum class Key {
	ESCAPE = GLFW_KEY_ESCAPE,
	LEFT = GLFW_KEY_LEFT,
	RIGHT = GLFW_KEY_RIGHT,
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN
};

class Input {
private:
	GLFWwindow* window;

	std::vector<bool> keyPressed;
	std::vector<bool> keyReleased;

	std::vector<bool> keyCurrentlyPressed;
public:
	Input(GLFWwindow* window);
	virtual ~Input();

	void update();

	void keyUpdate(int key, int action);

	bool isKeyPressed(Key key);
	bool isKeyCurrentlyPressed(Key key);
};

