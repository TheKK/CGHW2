#include <SDL_opengl.h>

#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

void GLWrapper::setClearColor(double r, double g, double b, double a)
{
	glClearColor(r, g, b, a);
}

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWrapper::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void GLWrapper::setPointColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void GLWrapper::drawLine(float x1, float y1, float x2, float y2)
{
	// Complete your code here, you can only use GLWrapper::drawPoint
	// To determine how many samples you want, You may need to calculate the pixel width
}
