#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Application.h"

int main() {
	// Initialize GLFW with OpenGL Version 3.3 and core profile.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the GLFW window with 1280*720 size.
	GLFWwindow* window = glfwCreateWindow(1280, 720, "slbpp", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create the application with this window pointer.
	Application application(window);
	application.run();

	// Terminate the GLFW window.
	glfwTerminate();
	return 0;
}