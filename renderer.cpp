#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "objLoader.h"
#include "glwrapper.h"
#include "helper.h"

#include "renderer.h"

Renderer::Renderer():
	_viewMatrix(glm::mat4(1.0)),
	_projectMatrix(glm::ortho(-1, 1, -1, 1, 0, 100)),
	_VPMatrix(_viewMatrix * _projectMatrix)
{
}

Renderer::Renderer(SDL_Window* window, enum RendererType type):
	_window(window),
	_viewMatrix(glm::mat4(1.0)),
	_projectMatrix(glm::ortho(-1, 1, -1, 1, 1, 100)),
	_VPMatrix(_viewMatrix * _projectMatrix)
{
	create(_window, type);
}

int
Renderer::create(SDL_Window* window, enum RendererType type)
{
	int w, h;

	if (!window)
		return -1;

	SDL_GetWindowSize(window, &w, &h);
	_window = window;
	_viewportWidth = _logicalWidth = w;
	_viewportHeight = _logicalHeight = h;

	_projectMatrix = glm::ortho(0, _viewportWidth, -_viewportHeight, 0,
				    1, 100);

	_updatePixelInfo();
	_updateVPMatrix();

	return 0;
}

void
Renderer::drawLine(int x0, int y0, int x1, int y1)
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

void
Renderer::drawPixel(int x, int y)
{
	float coordXPerPiexl = 2.f / (float) _logicalWidth;
	float coordYPerPiexl = 2.f / (float) _logicalHeight;

	float realX = -1.0 + ((0.5 + (float) x) * coordXPerPiexl);
	float realY = 1.0 - ((0.5 + (float) y) * coordYPerPiexl);

	GLWrapper::drawPoint(realX, realY);
}

void
Renderer::drawCircle(int cx, int cy, int r, int seg)
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

	
		Renderer::drawLine(x1, y1, x2, y2);
	}
}

void
Renderer::drawObj(const ObjLoader& loader)
{
	const std::vector<glm::vec3>& vertice = loader.getVertice();
	const std::vector<std::array<std::array<uint32_t, 3>, 3>>& faces = loader.getFaces();;
	std::array<glm::vec4, 3> pointsToDraw;

	for (const auto& face : faces) {
		pointsToDraw = {
			{
				glm::vec4(vertice[face[0][0]], 1.0),
				glm::vec4(vertice[face[1][0]], 1.0),
				glm::vec4(vertice[face[2][0]], 1.0)
			}
		};

		drawLine((_VPMatrix * pointsToDraw[0])[0], (_VPMatrix * pointsToDraw[0])[1],
			 (_VPMatrix * pointsToDraw[1])[0], (_VPMatrix * pointsToDraw[1])[1]);

		drawLine((_VPMatrix * pointsToDraw[1])[0], (_VPMatrix * pointsToDraw[1])[1],
			 (_VPMatrix * pointsToDraw[2])[0], (_VPMatrix * pointsToDraw[2])[1]);

		drawLine((_VPMatrix * pointsToDraw[2])[0], (_VPMatrix * pointsToDraw[2])[1],
			 (_VPMatrix * pointsToDraw[0])[0], (_VPMatrix * pointsToDraw[0])[1]);
	}
}

void
Renderer::setRenderLogicalSize(int w, int h)
{
	_logicalWidth = w;
	_logicalHeight = h;

	_updatePixelInfo();
}

void
Renderer::windowResizeHandler(int windowWidth, int windowHeight)
{
	float windowAspect = (float) windowWidth / (float) windowHeight;
	float viewportAspect = ((float) _logicalWidth /
				(float) _logicalHeight);

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

	_viewportWidth = viewportWidth;
	_viewportHeight = viewportHeight;

	_updatePixelInfo();
}


void
Renderer::setViewMatrix(const glm::mat4& mat)
{
	_viewMatrix = mat;

	_updateVPMatrix();
}

void
Renderer::setProjectMatrix(const glm::mat4& mat)
{
	_projectMatrix = mat;

	_updateVPMatrix();
}

void
Renderer::_updatePixelInfo()
{
	_pixelSize = std::ceil((float) _viewportWidth / (float) _logicalWidth);

	GLWrapper::setPointSize(_pixelSize);
}

void
Renderer::_updateVPMatrix()
{
	_VPMatrix = _viewMatrix;
}
