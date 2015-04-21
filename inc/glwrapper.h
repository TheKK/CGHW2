#ifndef _GLWRAPPER_H_
#define _GLWRAPPER_H_

namespace GLWrapper
{
	void setViewport(int x, int y, int w, int h);
	void setClearColor(double r, double g, double b, double a);
	void clearScreen();
	void setPointSize(int arg);
	void setDrawColor(float r, float g, float b);
	void drawPoint(float, float);
}

#endif
