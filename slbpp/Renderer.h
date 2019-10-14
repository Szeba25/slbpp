#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Point.h"
#include "Color.h"

class Renderer {
private:
	std::unique_ptr<Shader> shader;

	unsigned int maxQuads;

	GLfloat* vertices;
	GLuint* indices;

	unsigned int verticesId;
	unsigned int indicesId;
	unsigned int drawId;
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	std::shared_ptr<Texture> currentTexture;

	glm::mat4 projection;
	glm::mat4 view;

	unsigned int drawCalls;

	void flush();
public:
	Renderer();
	virtual ~Renderer();

	void clear();
	void start();
	void end();

	void translateView(float x, float y);

	void drawTexture(std::shared_ptr<Texture>& texture, Point start);
	void drawTexture(std::shared_ptr<Texture>& texture, Point start, Point dim);
	void drawTexture(std::shared_ptr<Texture>& texture, Point start, Color color);
	void drawTexture(std::shared_ptr<Texture>& texture, Point start, Point dim, Color color);

	void resize(int width, int height);

	void printDebug();
};

