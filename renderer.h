#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class ModelAsset;

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

	void drawPixel(int x, int y);
	void drawLine(int x0, int y0, int x1, int y1);
	void drawCircle(int x, int y, int r, int seg);

	void renderAsset(const ModelAsset& asset, const glm::mat4& modelMatrix);

	void setRenderLogicalSize(int w, int h);
	void windowResizeHandler(int windowWidth, int windowHeight);

	void setViewMatrix(const glm::mat4& mat);
	void setProjectMatrix(const glm::mat4& mat);
private:
	SDL_Window* _window;

	int _viewportWidth, _viewportHeight;
	int _logicalWidth, _logicalHeight;
	int _pixelSize;

	glm::mat4 _viewMatrix, _projectMatrix, _VPMatrix;

	/* TODO resource manager */
	std::map<std::string, std::weak_ptr<ModelAsset>> _modelAssets;

	void _updatePixelInfo();
	void _updateVPMatrix();
};

#endif /* RENDERER_H */
