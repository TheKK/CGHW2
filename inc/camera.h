#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	void setPosition(const glm::vec3& p);
	void offsetPosition(const glm::vec3& offset);
	const glm::vec3& getPosition() const;

	void offsetOrientation(float angleRight, float angleUp);
	glm::mat4 getOrientation() const;
	glm::mat4 getProjection() const;
	glm::mat4 getView() const;

	void setNearPlane(float n);
	void setFarPlane(float f);
	void setFov(float fov);
	void offsetFov(float dFov) { _fov += dFov; };
	void setViewportAspectRatio(float ratio);

	glm::vec3 getRight() const;
	glm::vec3 getLeft() const;
	glm::vec3 getForward() const;
	glm::vec3 getBackwrad() const;

	glm::mat4 getMatrix() const;
private:
	glm::vec3 _position;
	float _horizontalAngle, _verticalAngle;

	float _nearPlane, _farPlane, _fov, _viewportAspectRatio;

	void _normalizeAngles();
};

#endif /* CAMERA_H */
