#pragma once


#include "oglwin.h"
#include <glm/glm.hpp>

namespace ogl {

class Camera {
public:
	Camera(int width, int height);
	Camera(int width, int height, const glm::vec3& mPosition, const glm::vec3& front, const glm::vec3& up);


	const glm::vec3& position() const
	{
		return mPosition;
	}

	Camera& setPosition(const glm::vec3& position)
	{
		mPosition = position; return *this;
	}

	Camera& offsetPosition(const glm::vec3& offset)
	{
		mPosition += offset;
		return *this;
	}


	const glm::vec3& front() const
	{
		return mFront;
	}

	Camera& setFront(const glm::vec3& front)
	{
		mFront= front;
		return *this;
	}

	Camera& offsetFront(const glm::vec3& offset)
	{
		mFront += offset;
		return *this;
	}


	const glm::vec3& up() const
	{
		return mUp;
	}

	Camera& setUp(const glm::vec3& up)
	{
		mUp = up;
		return *this;
	}

	Camera& offsetUp(const glm::vec3& offset)
	{
		mUp += offset;
		return *this;
	}


	float fieldOfView() const
	{
		return mFovy;
	}

	Camera& setFieldOfView(float fov)
	{
		mFovy = fov;
		return *this;
	}


	float viewportAspectRatio() const
	{
		return mAspectRatio;
	}

	Camera& setViewportAspectRatio(float aspectRatio) {
		mAspectRatio = aspectRatio;
		return *this;
	}


	float zNear() const
	{
		return mZNear;
	}

	float zFar() const
	{
		return mZFar;
	}

	Camera& setNearAndFarPlanes(float zNear, float zFar)
	{
		mZFar = zFar;
		mZNear = zNear;
		return *this;
	}

	glm::mat4 matrix() const;


private:
	int mWidth;
	int mHeight;

	float mFovy = 45.0f;
	float mAspectRatio;
	float mZNear = 1.0f;
	float mZFar = 1000.0f;

	glm::vec3 mPosition;
	glm::vec3 mFront;
	glm::vec3 mUp;
};

} // namespace ogl
