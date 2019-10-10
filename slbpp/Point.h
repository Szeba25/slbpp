#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Point {
private:
	GLfloat x;
	GLfloat y;
public:
	Point(GLfloat x, GLfloat y);
	virtual ~Point();

	GLfloat getX();
	GLfloat getY();
};

