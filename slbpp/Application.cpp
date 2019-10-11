#include "Application.h"

void Application::update() {
	if (input->isKeyPressed(Key::ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
	if (input->isKeyCurrentlyPressed(Key::LEFT)) {
		renderer->translateView(5.0f, 0.0f);
	}
	if (input->isKeyCurrentlyPressed(Key::RIGHT)) {
		renderer->translateView(-5.0f, 0.0f);
	}
	if (input->isKeyCurrentlyPressed(Key::DOWN)) {
		renderer->translateView(0.0f, -5.0f);
	}
	if (input->isKeyCurrentlyPressed(Key::UP)) {
		renderer->translateView(0.0f, 5.0f);
	}
}

void Application::render() {
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
}

Application::Application(GLFWwindow* window) :
	window(window) {

	currentTime = std::chrono::high_resolution_clock::now();
	delta = std::chrono::nanoseconds(1000000000 / 60);
	maxAccumulator = delta * 5;
	accumulator = std::chrono::nanoseconds::zero();

	updatesPerSecond = 0;
	updateCounter = 0;
	resetTime = currentTime + std::chrono::seconds(1);

	input = new Input(window);
	renderer = new Renderer();

	glfwSetWindowUserPointer(window, this);

	auto bufferCallback = [](GLFWwindow* window, int width, int height) {
		static_cast<Application*>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(width, height);
	};

	auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		static_cast<Application*>(glfwGetWindowUserPointer(window))->keyCallback(key, action);
	};

	glfwSetFramebufferSizeCallback(window, bufferCallback);
	glfwSetKeyCallback(window, keyCallback);
}

Application::~Application() {
	delete renderer;
	delete input;
}

void Application::run() {
	// Loop until the GLFW window is closed.
	while (!glfwWindowShouldClose(window)) {
		// Set the new timepoint.
		std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;

		// Limit accumulator.
		if (accumulator > maxAccumulator) {
			accumulator = maxAccumulator;
		}

		while (accumulator >= delta) {
			update();
			input->update();
			updateCounter++;
			accumulator -= delta;
		}
		
		if (currentTime >= resetTime) {
			updatesPerSecond = updateCounter;
			updateCounter = 0;
			resetTime += std::chrono::seconds(1);
			std::cout << "UPS: " << updatesPerSecond << std::endl;
		}

		// Render as fast as possible.
		render();

		// Swap buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::framebufferSizeCallback(int width, int height) {
	std::cout << "Framebuffer size callback: " << width << " " << height << std::endl;
	renderer->resize(width, height);
}

void Application::keyCallback(int key, int action) {
	input->keyUpdate(key, action);
}
