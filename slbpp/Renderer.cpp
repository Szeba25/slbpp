#include "Renderer.h"

Renderer::Renderer() {
	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Create shaders.
	shader = std::make_unique<Shader>("test.vert", "test.frag");

	// Initialize vertices.
	vertices = new GLfloat[2048];
	index = 0;

	// Set up buffers.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 2048 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// Position.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	// Color.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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
	glBufferSubData(GL_ARRAY_BUFFER, 0, index * sizeof(GLfloat), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, index / 5);

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

	vertices[index + 5] = start.getX() + dim.getX();
	vertices[index + 6] = start.getY();
	vertices[index + 7] = color.getR();
	vertices[index + 8] = color.getG();
	vertices[index + 9] = color.getB();

	vertices[index + 10] = start.getX();
	vertices[index + 11] = start.getY() + dim.getY();
	vertices[index + 12] = color.getR();
	vertices[index + 13] = color.getG();
	vertices[index + 14] = color.getB();

	// Second triangle...
	vertices[index + 15] = start.getX() + dim.getX();
	vertices[index + 16] = start.getY();
	vertices[index + 17] = color.getR();
	vertices[index + 18] = color.getG();
	vertices[index + 19] = color.getB();

	vertices[index + 20] = start.getX();
	vertices[index + 21] = start.getY() + dim.getY();
	vertices[index + 22] = color.getR();
	vertices[index + 23] = color.getG();
	vertices[index + 24] = color.getB();

	vertices[index + 25] = start.getX() + dim.getX();
	vertices[index + 26] = start.getY() + dim.getY();
	vertices[index + 27] = color.getR();
	vertices[index + 28] = color.getG();
	vertices[index + 29] = color.getB();

	index += 30;
}

void Renderer::resize(int width, int height) {
	glViewport(0, 0, width, height);
}
