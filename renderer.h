#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "resourceManager.h"

class ModelAsset;
class ModelInstance;

enum RendererType {
	RENDERER_SOFTWARERENDER = 0x00,
	RENDERER_HARDWARERENDER
};

class Renderer
{
public:
	Renderer();
	Renderer(SDL_Window* window, enum RendererType type);

	int create(SDL_Window* window, enum RendererType type);

	std::shared_ptr<ModelAsset> loadObj(const std::string& filePath);

	void setClearColor(double r, double g, double b, double a);
	void setDrawColor(float r, float g, float b);
	void drawPixel(int x, int y);
	void drawLine(int x0, int y0, int x1, int y1);
	void drawCircle(int x, int y, int r, int seg);

	void clear();
	void present();

	void renderAsset(const ModelAsset& asset, const glm::mat4& modelMatrix);

	void setRenderLogicalSize(int w, int h);
	void windowResizeHandler(int windowWidth, int windowHeight);

	void setVPMatrix(const glm::mat4 matrix);
private:
	SDL_Window* _window;

	int _viewportWidth, _viewportHeight;
	int _logicalWidth, _logicalHeight;
	float _coordXPerPiexl, _coordYPerPiexl;
	int _pixelSize;
	glm::mat4 _VPMatrix, _MVPMatrix;

	ResourceManager<ModelAsset> _modelAssetManager;

	glm::vec4 _runVerticeShader(const glm::vec4& point);
	void _runFragmentShader(const std::array<glm::vec4, 3>& points);
	void _updatePixelInfo();
	void _updateVPMatrix();
};

#endif /* RENDERER_H */
