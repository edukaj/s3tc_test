#pragma once

#include "oglwin.h"
#include <glm/glm.hpp>

namespace ogl {

/**
	 A first-person shooter type of camera.
	 Set the properties of the camera, then use the `matrix` method to get the camera matrix for
	 use in the vertex shader.
	 Includes the perspective projection matrix.
	 */
class Camera {
public:
	Camera();

	const glm::vec3& position() const;
	void setPosition(const glm::vec3& position);
	void offsetPosition(const glm::vec3& offset);

	float fieldOfView() const;
	void setFieldOfView(float fieldOfView);

	float nearPlane() const;
	float farPlane() const;

	void setNearAndFarPlanes(float nearPlane, float farPlane);

	glm::mat4 orientation() const;
	void offsetOrientation(float upAngle, float rightAngle);

	void lookAt(glm::vec3 position);

	float viewportAspectRatio() const;
	void setViewportAspectRatio(float viewportAspectRatio);

	glm::vec3 forward() const;
	glm::vec3 right() const;
	glm::vec3 up() const;

	glm::mat4 matrix() const;
	glm::mat4 projection() const;
	glm::mat4 view() const;

private:
	glm::vec3 mPosition;
	float mHorizontalAngle;
	float mVerticalAngle;
	float mFieldOfView;
	float mNearPlane;
	float mFarPlane;
	float mViewportAspectRatio;

	void normalizeAngles();
};

} // namespace ogl
