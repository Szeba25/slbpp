#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

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

	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Set viewport resize callback function.
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Loop until the GLFW window is closed.
	while (!glfwWindowShouldClose(window)) {
		// Input.
		processInput(window);

		// Rendering.
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate the GLFW window.
	glfwTerminate();
	return 0;
}