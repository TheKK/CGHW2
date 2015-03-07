#include "hw2.h"
#include "glwrapper.h"
#include <cmath>

#ifndef M_PI
#define M_PI    3.1415926535
#endif

#define DEGREE2ARC(DEGREE) ((DEGREE) * M_PI / 180.0)

void HW2::drawCircle(float cx, float cy, float r, int seg)
{
	float degreeForEachSeg = (360.0 / (float) seg);
	float x1, y1, x2, y2;

	x1 = cx + r;
	y1 = 0;

	for (int i = 1; i <= seg; ++i) {
		if (i & 1) {
			x2 = cx + (r * cos(DEGREE2ARC(degreeForEachSeg * i)));
			y2 = cy + (r * sin(DEGREE2ARC(degreeForEachSeg * i)));
		} else {
			x1 = cx + (r * cos(DEGREE2ARC(degreeForEachSeg * i)));
			y1 = cy + (r * sin(DEGREE2ARC(degreeForEachSeg * i)));
		}

		GLWrapper::drawLine(x1, y1, x2, y2);
	}
}
