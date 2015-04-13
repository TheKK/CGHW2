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
class IVerticeShader;
class IFragmentShader;

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
	void drawPixel(float x, float y);
	void drawLine(int x0, int y0, int x1, int y1);
	void drawCircle(int x, int y, int r, int seg);

	void clear();
	void present();

	void setVerticeShader(IVerticeShader& vs)
	{ _currentVerticeShader = &vs; }

	void setFragmentShader(IFragmentShader& fs)
	{ _currentFragmentShader = &fs; }


	void renderAsset(const ModelAsset& asset);

	void setRenderLogicalSize(int w, int h);
	void windowResizeHandler(int windowWidth, int windowHeight);
private:
	SDL_Window* _window;

	int _viewportWidth, _viewportHeight;
	int _logicalWidth, _logicalHeight;
	float _coordXPerPiexl, _coordYPerPiexl;
	int _pixelSize;

	IVerticeShader* _currentVerticeShader = nullptr;
	IFragmentShader* _currentFragmentShader = nullptr;

	ResourceManager<ModelAsset> _modelAssetManager;

	void _rasterization(std::array<glm::vec4, 3>& points);
	void _updatePixelInfo();
};

#endif /* RENDERER_H */
