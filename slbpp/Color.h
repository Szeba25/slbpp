#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Color {
private:
	GLfloat r;
	GLfloat g;
	GLfloat b;
public:
	Color(GLfloat r, GLfloat g, GLfloat b);
	virtual ~Color();

	GLfloat getR();
	GLfloat getG();
	GLfloat getB();
};

