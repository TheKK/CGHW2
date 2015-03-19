#ifndef _HW1_H_
#define _HW1_H_

#include "objLoader.h"

namespace HW2
{
	void drawPixel(int x, int y);
	void drawLine(int x0, int y0, int x1, int y1);
	void drawCircle(int x, int y, int r, int seg);
	void drawObj(const ObjLoader& objLoader);
	// design your function interface here
	// ex.
	// Mesh *loadMesh(const char *filename)
	// void drawMesh(Mesh *) or someMeshObject->draw()
	// (You need to complete Mesh class on your own)

	void setRenderLogicalSize(int w, int h);
	void windowResizeHandler(int windowWidth, int windowHeight);
}

#endif
