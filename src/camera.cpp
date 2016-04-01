#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace ogl;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
	mPosition(0.0f, 0.0f, 1.0f),
	mHorizontalAngle(0.0f),
	mVerticalAngle(0.0f),
	mFieldOfView(50.0f),
	mNearPlane(0.01f),
	mFarPlane(100.0f),
	mViewportAspectRatio(4.0f/3.0f)
{
}

const glm::vec3& Camera::position() const {
	return mPosition;
}

void Camera::setPosition(const glm::vec3& position) {
	mPosition = position;
}

void Camera::offsetPosition(const glm::vec3& offset) {
	mPosition += offset;
}

float Camera::fieldOfView() const {
	return mFieldOfView;
}

void Camera::setFieldOfView(float fieldOfView) {
	assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
	mFieldOfView = fieldOfView;
}

float Camera::nearPlane() const {
	return mNearPlane;
}

float Camera::farPlane() const {
	return mFarPlane;
}

void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
}

glm::mat4 Camera::orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(mVerticalAngle), glm::vec3(1,0,0));
	orientation = glm::rotate(orientation, glm::radians(mHorizontalAngle), glm::vec3(0,1,0));
	return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle) {
	mHorizontalAngle += rightAngle;
	mVerticalAngle += upAngle;
	normalizeAngles();
}

void Camera::lookAt(glm::vec3 position) {
	assert(position != mPosition);
	glm::vec3 direction = glm::normalize(position - mPosition);
	mVerticalAngle = glm::radians(asinf(-direction.y));
	mHorizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
	normalizeAngles();
}

float Camera::viewportAspectRatio() const {
	return mViewportAspectRatio;
}

void Camera::setViewportAspectRatio(float viewportAspectRatio) {
	assert(viewportAspectRatio > 0.0);
	mViewportAspectRatio = viewportAspectRatio;
}

glm::vec3 Camera::forward() const {
	glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
	return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
	glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
	return glm::vec3(right);
}

glm::vec3 Camera::up() const {
	glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
	return glm::vec3(up);
}

glm::mat4 Camera::matrix() const {
	return projection() * view();
}

glm::mat4 Camera::projection() const {
	return glm::perspective(glm::radians(mFieldOfView), mViewportAspectRatio, mNearPlane, mFarPlane);
}

glm::mat4 Camera::view() const {
	return orientation() * glm::translate(glm::mat4(), -mPosition);
}

void Camera::normalizeAngles() {
	mHorizontalAngle = fmodf(mHorizontalAngle, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if(mHorizontalAngle < 0.0f)
		mHorizontalAngle += 360.0f;

	if(mVerticalAngle > MaxVerticalAngle)
		mVerticalAngle = MaxVerticalAngle;
	else if(mVerticalAngle < -MaxVerticalAngle)
		mVerticalAngle = -MaxVerticalAngle;
}
