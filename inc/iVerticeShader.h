#ifndef I_VERTICE_SHADER_H
#define I_VERTICE_SHADER_H

#include <glm/glm.hpp>

class IVerticeShader
{
public:
	virtual void doVerticeShade(glm::vec4& point) = 0;
};

#endif /* I_VERTICE_SHADER_H */
