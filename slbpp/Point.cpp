#include "Point.h"

Point::Point(GLfloat x, GLfloat y) :
	x(x),
	y(y)
{

}

Point::~Point() {
}

GLfloat Point::getX() {
	return x;
}

GLfloat Point::getY() {
	return y;
}
