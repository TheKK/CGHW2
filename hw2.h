#ifndef _HW1_H_
#define _HW1_H_

namespace HW2
{
	void drawPixel(int x, int y);
	void drawCircle(float x, float y, float r, int seg);
	// design your function interface here
	// ex.
	// Mesh *loadMesh(const char *filename)
	// void drawMesh(Mesh *) or someMeshObject->draw()
	// (You need to complete Mesh class on your own)

	void setRenderLogicalSize(int w, int h);
	void windowResizeHandler(int windowWidth, int windowHeight);
}

#endif
