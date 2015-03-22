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

void GLWrapper::drawLine(float x1, float y1, float x2, float y2)
{
	/* TODO Use greater algorithm if possible */
	float tx, ty;
	float dx = x2 - x1;
	float dy = y2 - y1;
	const int stop = 20;
	int step = 0;

	glBegin(GL_POINTS);
	glVertex2f(x1, y1);

	while (1) {
		++step;
		if (step > stop)
			break;

		tx = x1 + dx * ((double) step / (double) stop);
		ty = y1 + dy * ((double) step / (double) stop);
		glVertex2f(tx, ty);
	}

	glVertex2f(x2, y2);
	glEnd();
}
