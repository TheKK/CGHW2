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

	glm::vec3 getRight() const;
	glm::vec3 getLeft() const;
	glm::vec3 getForward() const;
	glm::vec3 getBackwrad() const;

	glm::mat4 getViewMatrix() const;
private:
	glm::vec3 _position;
	float _horizontalAngle, _verticalAngle;

	void _normalizeAngles();
};

#endif /* CAMERA_H */
