#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class Key {
	ESCAPE = GLFW_KEY_ESCAPE
};

class Input {
private:
	GLFWwindow* window;
public:
	Input(GLFWwindow* window);
	virtual ~Input();

	bool isKeyPressed(Key key);
};

