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
	GLfloat* vertices;
	GLuint* indices;
	unsigned int verticesId;
	unsigned int indicesId;
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::unique_ptr<Texture> testTexture;

	glm::mat4 projection;
	glm::mat4 view;
public:
	Renderer();
	virtual ~Renderer();

	void clear();
	void start();
	void flush();

	void translateView(float x, float y);

	void drawRectangle(Point start, Point dim, Color color);

	void resize(int width, int height);
};

