#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

#include "modelAsset.h"
#include "glwrapper.h"
#include "modelInstance.h"
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

	_projectMatrix = glm::ortho(0.f, (float) _viewportWidth,
				    (float) -_viewportHeight, 0.f,
				    1.f, 100.f);

	_updatePixelInfo();
	_updateVPMatrix();

	return 0;
}

std::shared_ptr<ModelAsset>
Renderer::loadObj(const std::string& filePath)
{
	return _modelAssetManager.aquire(filePath);
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
Renderer::setClearColor(double r, double g, double b, double a)
{
	GLWrapper::setClearColor(r, g, b, a);
}

void
Renderer::setDrawColor(float r, float g, float b)
{
	GLWrapper::setDrawColor(r, g, b);
}

void
Renderer::drawPixel(int x, int y)
{

	float realX = ((0.5 + (float) x) * _coordXPerPiexl);
	float realY = ((0.5 + (float) y) * _coordYPerPiexl);

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
Renderer::clear()
{
	GLWrapper::clearScreen();
}

void
Renderer::present()
{
	SDL_GL_SwapWindow(_window);
}

void
Renderer::renderAsset(const ModelAsset& asset, const glm::mat4& modelMatrix)
{
	const std::vector<glm::vec3>& vertice = asset.getVertice();
	const std::vector<std::array<std::array<uint32_t, 3>, 3>>& faces =
		asset.getFaces();
	const glm::mat4 MVPMatrix = _VPMatrix * modelMatrix;
	std::array<glm::vec4, 3> pointsToDraw;

	for (const auto& face : faces) {
		pointsToDraw = {
			{
				glm::vec4(vertice[face[0][0]], 1.0),
				glm::vec4(vertice[face[1][0]], 1.0),
				glm::vec4(vertice[face[2][0]], 1.0)
			}
		};

		for (auto& e : pointsToDraw)
			e = MVPMatrix * e;

		drawLine(pointsToDraw[0][0], pointsToDraw[0][1],
			 pointsToDraw[1][0], pointsToDraw[1][1]);

		drawLine(pointsToDraw[1][0], pointsToDraw[1][1],
			 pointsToDraw[2][0], pointsToDraw[2][1]);

		drawLine(pointsToDraw[2][0], pointsToDraw[2][1],
			 pointsToDraw[0][0], pointsToDraw[0][1]);
	}
}

void
Renderer::setRenderLogicalSize(int w, int h)
{
	_logicalWidth = w;
	_logicalHeight = h;

	_coordXPerPiexl = 2.f / (float) _logicalWidth;
	_coordYPerPiexl = 2.f / (float) _logicalHeight;

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
		viewportWidth = std::round((float) windowHeight *
					   viewportAspect);
		viewportHeight = windowHeight;

		horizontalBlankOffset = (windowWidth - viewportWidth) / 2;
		virticalBlankOffset = 0;

	} else if (windowAspect < viewportAspect) {
		viewportWidth = windowWidth;
		viewportHeight = std::round((float) windowWidth /
					    viewportAspect);

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
Renderer::setViewPort(int x, int y, int w, int h)
{
	_viewportMatrix[0] = glm::vec4((float) w / 2.f, 0.f, 0.f,
				       (float) w / 2.f + x);
	_viewportMatrix[1] = glm::vec4(0.f, (float) h / 2.f, 0.f,
				       (float) h / 2.f + y);
	_viewportMatrix[2] = glm::vec4(0.f, 0.f, 0.f, 0.f);
	_viewportMatrix[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);

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
	_VPMatrix = _projectMatrix * _viewMatrix;
}
