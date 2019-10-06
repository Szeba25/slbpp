#include "Input.h"

Input::Input(GLFWwindow* window) : 
	window(window) {
}

Input::~Input() {

}

bool Input::isKeyPressed(Key key) {
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
}
