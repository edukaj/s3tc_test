#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace ogl;

Camera::Camera(int width, int height)
	: mWidth{width}, mHeight{height},
	  mPosition{0.0f, 0.0f, 0.0f},
	  mFront{0.0f, 0.0f, -1.0f},
	  mUp{0.0f, 1.0f, 0.0f}
{
}

Camera::Camera(int width, int height, const glm::vec3 &position, const glm::vec3 &front, const glm::vec3 &up)
	: mWidth{width}, mHeight{height},
	  mPosition{position}, mFront{front}, mUp{up}
{
}

glm::mat4 Camera::matrix() const
{
	return glm::perspective(mFovy, mAspectRatio, mZNear, mZFar) *
			glm::lookAt(mPosition, mPosition + mFront, mUp);
}


