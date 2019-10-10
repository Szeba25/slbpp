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
		if (input->isKeyPressed(Key::LEFT)) {
			renderer->translateView(1.0f, 0.0f);
		}
		if (input->isKeyPressed(Key::RIGHT)) {
			renderer->translateView(-1.0f, 0.0f);
		}
		if (input->isKeyPressed(Key::DOWN)) {
			renderer->translateView(0.0f, -1.0f);
		}
		if (input->isKeyPressed(Key::UP)) {
			renderer->translateView(0.0f, 1.0f);
		}

		// Rendering.
		renderer->clear();
		renderer->start();

		renderer->drawTriangle(
			Point(10, 10), 
			Point(300, 160), 
			Point(10, 310), 
			Color(0.6f, 0.9f, 0.3f)
		);
		renderer->drawTriangle(
			Point(450, 30), 
			Point(470, 500), 
			Point(590, 650), 
			Color(0.7f, 0.1f, 0.2f)
		);

		renderer->flush();

		// Swap buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::framebufferSizeCallback(int width, int height) {
	std::cout << "Framebuffer size callback: " << width << " " << height << std::endl;
	renderer->resize(width, height);
}
