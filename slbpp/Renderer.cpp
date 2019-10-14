#include "Renderer.h"

Renderer::Renderer() {
	// Set the viewport to match the window size.
	glViewport(0, 0, 1280, 720);

	// Create shaders.
	shader = std::make_unique<Shader>("test.vert", "test.frag");

	// Initialize vertices.
	long long int maxSprites = 256;

	vertices = new GLfloat[maxSprites * 28];
	indices = new GLuint[maxSprites * 6];

	for (int i = 0; i < maxSprites; i++) {
		indices[(i * 6) + 0] = (i * 4) + 0;
		indices[(i * 6) + 1] = (i * 4) + 1;
		indices[(i * 6) + 2] = (i * 4) + 2;
		indices[(i * 6) + 3] = (i * 4) + 1;
		indices[(i * 6) + 4] = (i * 4) + 2;
		indices[(i * 6) + 5] = (i * 4) + 3;
	}

	verticesId = 0;
	indicesId = 0;

	// Set up buffers.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, maxSprites * 42 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxSprites * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

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
	// Do not unbind EBO!
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	glDeleteBuffers(1, &EBO);
	delete[] vertices;
	delete[] indices;
}

void Renderer::clear() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::start() {
	// Reset indexes!
	verticesId = 0;
	indicesId = 0;
}

void Renderer::end() {
	// Just flush the batch!
	flush();
}

void Renderer::flush() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 1. Buffer sub data method...
	//glBufferSubData(GL_ARRAY_BUFFER, 0, index * sizeof(GLfloat), vertices);

	// 2. Map buffer method...
	void* pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(pointer, vertices, verticesId * sizeof(GLfloat));
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	// bind texture!
	currentTexture->bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesId, GL_UNSIGNED_INT, 0);

	// Unnecessary to unbind every time!
	//glBindVertexArray(0);

	// Reset indexes!
	verticesId = 0;
	indicesId = 0;
}

void Renderer::translateView(float x, float y) {
	view = glm::translate(view, glm::vec3(x, y, 0.0f));
}

void Renderer::drawTexture(std::shared_ptr<Texture>& texture, Point start, Point dim, Color color) {
	if (currentTexture != texture && verticesId > 0) {
		flush();
	}
	currentTexture = texture;

	vertices[verticesId + 0] = start.getX();
	vertices[verticesId + 1] = start.getY();
	vertices[verticesId + 2] = color.getR();
	vertices[verticesId + 3] = color.getG();
	vertices[verticesId + 4] = color.getB();
	vertices[verticesId + 5] = 0.0f;
	vertices[verticesId + 6] = 0.0f;

	vertices[verticesId + 7] = start.getX() + dim.getX();
	vertices[verticesId + 8] = start.getY();
	vertices[verticesId + 9] = color.getR();
	vertices[verticesId + 10] = color.getG();
	vertices[verticesId + 11] = color.getB();
	vertices[verticesId + 12] = 1.0f;
	vertices[verticesId + 13] = 0.0f;

	vertices[verticesId + 14] = start.getX();
	vertices[verticesId + 15] = start.getY() + dim.getY();
	vertices[verticesId + 16] = color.getR();
	vertices[verticesId + 17] = color.getG();
	vertices[verticesId + 18] = color.getB();
	vertices[verticesId + 19] = 0.0f;
	vertices[verticesId + 20] = 1.0f;

	vertices[verticesId + 21] = start.getX() + dim.getX();
	vertices[verticesId + 22] = start.getY() + dim.getY();
	vertices[verticesId + 23] = color.getR();
	vertices[verticesId + 24] = color.getG();
	vertices[verticesId + 25] = color.getB();
	vertices[verticesId + 26] = 1.0f;
	vertices[verticesId + 27] = 1.0f;

	verticesId += 28;
	indicesId += 6;
}

void Renderer::resize(int width, int height) {
	glViewport(0, 0, width, height);
}
