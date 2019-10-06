#include "Application.h"

Application::Application(GLFWwindow* window) : 
	window(window) {
	
	input = new Input(window);
	renderer = new Renderer();

	glfwSetWindowUserPointer(window, this);
	auto callback = [](GLFWwindow* window, int width, int height) {
		static_cast<Application*>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(width, height);
	};

	glfwSetFramebufferSizeCallback(window, callback);
}

Application::~Application() {
	delete renderer;
	delete input;
}

void Application::run() {
	// Loop until the GLFW window is closed.
	while (!glfwWindowShouldClose(window)) {
		// Input.
		if (input->isKeyPressed(Key::ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}

		// Rendering.
		renderer->clear();

		// Swap buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::framebufferSizeCallback(int width, int height) {
	std::cout << "Framebuffer size callback: " << width << " " << height << std::endl;
	renderer->resize(width, height);
}
