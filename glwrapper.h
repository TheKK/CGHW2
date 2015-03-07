#ifndef _GLWRAPPER_H_
#define _GLWRAPPER_H_

namespace GLWrapper
{
	void setClearColor(double r, double g, double b, double a);
	void clearScreen();

	void setDrawColor(float r, float g, float b);
	void drawPoint(float, float);
	void drawLine(float x1, float y1, float x2, float y2);
}

#endif
