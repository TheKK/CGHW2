#include "hw2.h"
#include "glwrapper.h"
#include <SDL_opengl.h>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI    3.1415926535
#endif

#define DEGREE2ARC(DEGREE) ((DEGREE) * M_PI / 180.0)

struct Renderer {
	int viewportWidth, viewportHeight;
	int logicalWidth, logicalHeight;
	int pixelSize;
};
static Renderer renderer;

static void updatePixelInfo()
{
	renderer.pixelSize = floor((float) renderer.viewportWidth /
				   (float) renderer.logicalWidth);

	glPointSize(renderer.pixelSize);
}

void HW2::drawLine(int x0, int y0, int x1, int y1)
{
	int dx, dy;
	int error;
	int yStep, yCurrent;
	bool isSteep = abs(y1 - y0) > abs(x1 - x0);

	if (isSteep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	dx = x1 - x0;
	dy = abs(y1 - y0);
	error = dx / 2;
	yCurrent = y0;

	if (y0 < y1)
		yStep = 1;
	else
		yStep = -1;

	for (int xCurrent = x0; xCurrent <= x1; ++xCurrent) {
		if (isSteep)
			drawPixel(yCurrent, xCurrent);
		else
			drawPixel(xCurrent, yCurrent);

		error -= dy;
		if (error < 0) {
			yCurrent += yStep;
			error += dx;
		}
	}
}

void HW2::drawPixel(int x, int y)
{
	float coordXPerPiexl = 2.f / (float) renderer.logicalWidth;
	float coordYPerPiexl = 2.f / (float) renderer.logicalHeight;

	float realX = -1.0 + ((0.5 + (float) x) * coordXPerPiexl);
	float realY = 1.0 - ((0.5 + (float) y) * coordYPerPiexl);

	GLWrapper::drawPoint(realX, realY);
}

void HW2::drawCircle(int cx, int cy, int r, int seg)
{
	float degreeForEachSeg = (360.0 / (float) seg);
	float x1, y1, x2, y2;

	x1 = cx + r;
	y1 = cy;

	for (int i = 1; i <= seg; ++i) {
		if (i & 1) {
			x2 = cx + (r * cos(DEGREE2ARC(degreeForEachSeg * i)));
			y2 = cy + (r * sin(DEGREE2ARC(degreeForEachSeg * i)));
		} else {
			x1 = cx + (r * cos(DEGREE2ARC(degreeForEachSeg * i)));
			y1 = cy + (r * sin(DEGREE2ARC(degreeForEachSeg * i)));
		}

		HW2::drawLine(x1, y1, x2, y2);
	}
}

void HW2::setRenderLogicalSize(int w, int h)
{
	renderer.logicalWidth = w;
	renderer.logicalHeight = h;

	updatePixelInfo();
}

void HW2::windowResizeHandler(int windowWidth, int windowHeight)
{
	float windowAspect = (float) windowWidth / (float) windowHeight;
	float viewportAspect = ((float) renderer.logicalWidth /
				(float) renderer.logicalHeight);

	int viewportWidth, viewportHeight;
	int horizontalBlankOffset, virticalBlankOffset;

	if (windowAspect > viewportAspect) {
		viewportWidth = floor((float) windowHeight * viewportAspect);
		viewportHeight = windowHeight;

		horizontalBlankOffset = (windowWidth - viewportWidth) / 2;
		virticalBlankOffset = 0;

	} else if (windowAspect < viewportAspect) {
		viewportWidth = windowWidth;
		viewportHeight = floor((float) windowWidth / viewportAspect);

		horizontalBlankOffset = 0;
		virticalBlankOffset = (windowHeight - viewportHeight) / 2;

	} else if (windowAspect == viewportAspect) {
		viewportWidth = windowWidth;
		viewportHeight = windowHeight;

		horizontalBlankOffset = 0;
		virticalBlankOffset = 0;
	}

	GLWrapper::setViewport(horizontalBlankOffset, virticalBlankOffset,
			       viewportWidth, viewportHeight);

	renderer.viewportWidth = viewportWidth;
	renderer.viewportHeight = viewportHeight;

	updatePixelInfo();
}
