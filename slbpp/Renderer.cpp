#include "Renderer.h"

Renderer::Renderer() {
	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Create shaders.
	shader = std::make_unique<Shader>("test.vert", "test.frag");

	// Initialize vertices.
	vertices = new GLfloat[256 * 42];
	index = 0;

	// Set up buffers.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 256 * 42 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// Position.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	// Color.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture.
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Test texture...
	testTexture = std::make_unique<Texture>("test.png");

	// Matrices.
	projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -0.1f, 0.1f);
	view = glm::mat4(1.0f);

	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	// Polygon mode.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete[] vertices;
}

void Renderer::clear() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::start() {
	index = 0;
}

void Renderer::flush() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 1. Buffer sub data method...
	//glBufferSubData(GL_ARRAY_BUFFER, 0, index * sizeof(GLfloat), vertices);

	// 2. Map buffer method...
	void* pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(pointer, vertices, index * sizeof(GLfloat));
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	// bind texture!
	testTexture->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, index / 7);

	// Unnecessary to unbind every time!
	//glBindVertexArray(0);
}

void Renderer::translateView(float x, float y) {
	view = glm::translate(view, glm::vec3(x, y, 0.0f));
}

void Renderer::drawRectangle(Point start, Point dim, Color color) {
	// First triangle...
	vertices[index + 0] = start.getX();
	vertices[index + 1] = start.getY();
	vertices[index + 2] = color.getR();
	vertices[index + 3] = color.getG();
	vertices[index + 4] = color.getB();
	vertices[index + 5] = 0.0f;
	vertices[index + 6] = 0.0f;

	vertices[index + 7] = start.getX() + dim.getX();
	vertices[index + 8] = start.getY();
	vertices[index + 9] = color.getR();
	vertices[index + 10] = color.getG();
	vertices[index + 11] = color.getB();
	vertices[index + 12] = 1.0f;
	vertices[index + 13] = 0.0f;

	vertices[index + 14] = start.getX();
	vertices[index + 15] = start.getY() + dim.getY();
	vertices[index + 16] = color.getR();
	vertices[index + 17] = color.getG();
	vertices[index + 18] = color.getB();
	vertices[index + 19] = 0.0f;
	vertices[index + 20] = 1.0f;

	// Second triangle...
	vertices[index + 21] = start.getX() + dim.getX();
	vertices[index + 22] = start.getY();
	vertices[index + 23] = color.getR();
	vertices[index + 24] = color.getG();
	vertices[index + 25] = color.getB();
	vertices[index + 26] = 1.0f;
	vertices[index + 27] = 0.0f;

	vertices[index + 28] = start.getX();
	vertices[index + 29] = start.getY() + dim.getY();
	vertices[index + 30] = color.getR();
	vertices[index + 31] = color.getG();
	vertices[index + 32] = color.getB();
	vertices[index + 33] = 0.0f;
	vertices[index + 34] = 1.0f;

	vertices[index + 35] = start.getX() + dim.getX();
	vertices[index + 36] = start.getY() + dim.getY();
	vertices[index + 37] = color.getR();
	vertices[index + 38] = color.getG();
	vertices[index + 39] = color.getB();
	vertices[index + 40] = 1.0f;
	vertices[index + 41] = 1.0f;

	index += 42;
}

void Renderer::resize(int width, int height) {
	glViewport(0, 0, width, height);
}
