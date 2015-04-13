#ifndef I_FRAGMENT_SHADER_H
#define I_FRAGMENT_SHADER_H

#include <glm/glm.hpp>

class IFragmentShader
{
public:
	virtual glm::vec4 doFragmentShade(glm::vec4& point) = 0;
};

#endif /* I_FRAGMENT_SHADER_H */
