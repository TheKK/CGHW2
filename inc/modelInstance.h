#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "modelAsset.h"
#include "renderer.h"

class ModelInstance
{
public:
	ModelInstance();
	ModelInstance(Renderer& renderer, const std::string& filePath);

	void load(Renderer& renderer, const std::string& filePath);
	void render(Renderer& renderer);

	void setModelMatrix(const glm::mat4& matrix);
	const glm::mat4& getModelMatrix() const;
private:
	std::shared_ptr<ModelAsset> _asset;

	glm::mat4 _modelMatrix;
};

#endif /* MODEL_INSTANCE_H */
