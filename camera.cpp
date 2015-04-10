#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

namespace
{
	const float kMaxVerticalAngle = 85;
}

Camera::Camera():
	_position(0.f),
	_horizontalAngle(0.f),
	_verticalAngle(0.f)
{
}

void
Camera::setPosition(const glm::vec3& p)
{
	_position = p;
}

void
Camera::offsetPosition(const glm::vec3& offset)
{
	_position += offset;
}

const glm::vec3&
Camera::getPosition() const
{
	return _position;
}

void
Camera::offsetOrientation(float angleRight, float angleUp)
{
	_horizontalAngle += angleRight;
	_verticalAngle += angleUp;

	_normalizeAngles();
}

glm::mat4
Camera::getOrientation() const
{
	glm::mat4 viewMatrix;

	viewMatrix = glm::rotate(viewMatrix, -_horizontalAngle,
				 glm::vec3(0, 1, 0));
	viewMatrix = glm::rotate(viewMatrix, -_verticalAngle,
				 glm::vec3(0, 1, 0));

	return viewMatrix;
}

glm::vec3
Camera::getRight() const
{
	glm::vec4 right;

	right = glm::inverse(getOrientation()) * glm::vec4(1.f, 0.f, 0.f, 1.f);

	return glm::vec3(right);
}

glm::vec3
Camera::getLeft() const
{
	glm::vec4 left;

	left = glm::inverse(getOrientation()) * glm::vec4(-1.f, 0.f, 0.f, 1.f);

	return glm::vec3(left);
}

glm::vec3
Camera::getForward() const
{
	glm::vec4 fwd;

	fwd = glm::inverse(getOrientation()) * glm::vec4(0.f, 0.f, -1.f, 1.f);

	return glm::vec3(fwd);
}

glm::vec3
Camera::getBackwrad() const
{
	glm::vec4 bwd;

	bwd = glm::inverse(getOrientation()) * glm::vec4(0.f, 0.f, 1.f, 1.f);

	return glm::vec3(bwd);
}

glm::mat4
Camera::getViewMatrix() const
{
	return (getOrientation() * glm::translate(glm::mat4(), -_position));
}

void
Camera::_normalizeAngles()
{
	 _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
	 if(_horizontalAngle < 0.0f)
		 _horizontalAngle += 360.0f;

	 if(_verticalAngle > kMaxVerticalAngle)
		 _verticalAngle = kMaxVerticalAngle;
	 else if(_verticalAngle < -kMaxVerticalAngle)
		 _verticalAngle = -kMaxVerticalAngle;
}
