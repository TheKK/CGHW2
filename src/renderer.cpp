#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "modelAsset.h"
#include "glwrapper.h"
#include "modelInstance.h"
#include "helper.h"
#include "iVerticeShader.h"
#include "iFragmentShader.h"

#include "renderer.h"

Renderer::Renderer():
	_frameBuffer(10, 10)
{
}

Renderer::Renderer(SDL_Window* window, enum RendererType type):
	_window(window),
	_frameBuffer(10, 10)
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
	_viewportWidth = w;
	_viewportHeight = h;

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
	glm::vec4 color(r, g, b, 1.f);

	_frameBuffer.setClearColor(color);
}

void
Renderer::setDrawColor(float r, float g, float b)
{
	glm::vec4 color(r, g, b, 1.f);

	_frameBuffer.setDrawColor(color);
}

void
Renderer::drawPixel(int x, int y)
{
	_frameBuffer.drawPixel((uint32_t) x, (uint32_t) y);	
}

void
Renderer::drawPixel(float x, float y)
{
	_frameBuffer.drawPixel(x, y);
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
	_frameBuffer.clear(COLOR_BUFFER_BIT);
}

void
Renderer::present()
{
	_frameBuffer.upload();

	SDL_GL_SwapWindow(_window);
}

void
Renderer::renderAsset(const ModelAsset& asset)
{
	const std::vector<glm::vec3>& vertice = asset.getVertice();
	const std::vector<std::array<std::array<uint32_t, 3>, 3>>& faces =
		asset.getFaces();
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
			_currentVerticeShader->doVerticeShade(e);

		_rasterization(pointsToDraw);
	}
}

void
Renderer::setRenderLogicalSize(int w, int h)
{
}

void
Renderer::windowResizeHandler(int windowWidth, int windowHeight)
{
	//float windowAspect = (float) windowWidth / (float) windowHeight;
	//float viewportAspect = ((float) _logicalWidth /
				//(float) _logicalHeight);

	//int viewportWidth, viewportHeight;
	//int horizontalBlankOffset, virticalBlankOffset;

	//if (windowAspect > viewportAspect) {
		//viewportWidth = std::round((float) windowHeight *
					   //viewportAspect);
		//viewportHeight = windowHeight;

		//horizontalBlankOffset = (windowWidth - viewportWidth) / 2;
		//virticalBlankOffset = 0;

	//} else if (windowAspect < viewportAspect) {
		//viewportWidth = windowWidth;
		//viewportHeight = std::round((float) windowWidth /
					    //viewportAspect);

		//horizontalBlankOffset = 0;
		//virticalBlankOffset = (windowHeight - viewportHeight) / 2;

	//} else if (windowAspect == viewportAspect) {
		//viewportWidth = windowWidth;
		//viewportHeight = windowHeight;

		//horizontalBlankOffset = 0;
		//virticalBlankOffset = 0;
	//}

	//GLWrapper::setViewport(horizontalBlankOffset, virticalBlankOffset,
			       //viewportWidth, viewportHeight);

	//_viewportWidth = viewportWidth;
	//_viewportHeight = viewportHeight;
}

void 
Renderer::_rasterization(std::array<glm::vec4, 3>& points)
{
	glm::vec4& pointO = points[0];
	glm::vec4& pointA = points[1];
	glm::vec4& pointB = points[2];

	glm::vec4 colorToDraw;

	if (std::abs(pointO.z / pointO.w) <= 1.f) {
		colorToDraw = _currentFragmentShader->doFragmentShade(pointO);
		setDrawColor(colorToDraw[0], colorToDraw[1], colorToDraw[2]);
		drawPixel(pointO.x / pointO.w, pointO.y / pointO.w);
	}
	if (std::abs(pointA.z / pointA.w) <= 1.f) {
		colorToDraw = _currentFragmentShader->doFragmentShade(pointA);
		setDrawColor(colorToDraw[0], colorToDraw[1], colorToDraw[2]);
		drawPixel(pointA.x / pointA.w, pointA.y / pointA.w);
	}
	if (std::abs(pointB.z / pointB.w) <= 1.f) {
		colorToDraw = _currentFragmentShader->doFragmentShade(pointB);
		setDrawColor(colorToDraw[0], colorToDraw[1], colorToDraw[2]);
		drawPixel(pointB.x / pointB.w, pointB.y / pointB.w);
	}
}
