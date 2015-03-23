#include <SDL_opengl.h>

#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

void GLWrapper::setViewport(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
}

void GLWrapper::setClearColor(double r, double g, double b, double a)
{
	glClearColor(r, g, b, a);
}

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWrapper::setPointSize(int arg)
{
	glPointSize(arg);
}

void GLWrapper::setDrawColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void GLWrapper::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
