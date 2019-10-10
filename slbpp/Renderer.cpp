#include "Renderer.h"

Renderer::Renderer() {
	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Create shaders.
	shader = std::make_unique<Shader>("test.vert", "test.frag");

	// Initialize vertices.
	vertices = new GLfloat[300];
	index = 0;

	// Set up VBO and VAO.

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 300 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// Position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	// Color.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Matrices.
	projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -0.1f, 0.1f);
	view = glm::mat4(1.0f);

	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
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
	glBufferSubData(GL_ARRAY_BUFFER, 0, index * sizeof(GLfloat), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->use();

	glBindVertexArray(VAO);

	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	glDrawArrays(GL_TRIANGLES, 0, index / 6);

	// Unnecessary to unbind every time!
	//glBindVertexArray(0);
}

void Renderer::translateView(float x, float y) {
	view = glm::translate(view, glm::vec3(x, y, 0.0f));
}

void Renderer::drawTriangle(Point a, Point b, Point c, Color color) {
	vertices[index + 0] = a.getX();
	vertices[index + 1] = a.getY();
	vertices[index + 2] = 0.0f;
	vertices[index + 3] = color.getR();
	vertices[index + 4] = color.getG();
	vertices[index + 5] = color.getB();

	vertices[index + 6] = b.getX();
	vertices[index + 7] = b.getY();
	vertices[index + 8] = 0.0f;
	vertices[index + 9] = color.getR();
	vertices[index + 10] = color.getG();
	vertices[index + 11] = color.getB();

	vertices[index + 12] = c.getX();
	vertices[index + 13] = c.getY();
	vertices[index + 14] = 0.0f;
	vertices[index + 15] = color.getR();
	vertices[index + 16] = color.getG();
	vertices[index + 17] = color.getB();
	index += 18;
}

void Renderer::resize(int width, int height) {
	glViewport(0, 0, width, height);
}
