#include "Color.h"

Color::Color(GLfloat r, GLfloat g, GLfloat b) :
	r(r),
	g(g),
	b(b)
{
}

Color::~Color() {
}

GLfloat Color::getR() {
	return r;
}

GLfloat Color::getG() {
	return g;
}

GLfloat Color::getB() {
	return b;
}
