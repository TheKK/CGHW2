#ifndef IMP_RANDOM_FRAGMENT_SHADER
#define IMP_RANDOM_FRAGMENT_SHADER

#include <glm/glm.hpp>

#include "iFragmentShader.h"

class ImpRandomFragmentShader: public IFragmentShader
{
public:
	ImpRandomFragmentShader() {};

	virtual glm::vec4 doFragmentShade(glm::vec4& point)
	{
		return glm::vec4((float) rand() / (float) RAND_MAX,
				 (float) rand() / (float) RAND_MAX,
				 (float) rand() / (float) RAND_MAX,
				 1.f);
	};

	void setColor(const glm::vec3 color) { _colorToDraw = color; };
private:
	glm::vec3 _colorToDraw;
};

#endif /* IMP_RANDOM_FRAGMENT_SHADER */
