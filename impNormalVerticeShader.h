#ifndef IMP_NORMAL_VERTICE_SHADER_H
#define IMP_NORMAL_VERTICE_SHADER_H

#include <glm/glm.hpp>

#include "iVerticeShader.h"

class ImpNormalVerticeShader: public IVerticeShader
{
public:
	ImpNormalVerticeShader() {};

	virtual void doVerticeShade(glm::vec4& point) { point = _MVPMatrix * point; };

	void setMVPMatrix(const glm::mat4 mvp) { _MVPMatrix = mvp; };
private:
	glm::mat4 _MVPMatrix;
};

#endif /* IMP_NORMAL_VERTICE_SHADER_H */
