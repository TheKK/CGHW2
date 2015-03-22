#include "modelInstance.h"


ModelInstance::ModelInstance():
	_modelMatrix(1.0)
{
}

ModelInstance::ModelInstance(Renderer& renderer, const std::string& filePath):
	_modelMatrix(1.0)
{
	load(renderer, filePath);
}

void
ModelInstance::load(Renderer& renderer, const std::string& filePath)
{
	_asset= renderer.loadObj(filePath);
}

void
ModelInstance::render(Renderer& renderer)
{
	renderer.renderAsset(*_asset, _modelMatrix);
}

void
ModelInstance::setModelMatrix(const glm::mat4& matrix)
{
	_modelMatrix = matrix;
}
