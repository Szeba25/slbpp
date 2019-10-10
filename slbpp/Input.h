#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
public:
	Input(GLFWwindow* window);
	virtual ~Input();

	bool isKeyPressed(Key key);
};

