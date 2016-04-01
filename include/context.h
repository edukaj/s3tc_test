#pragma once

namespace ogl {

enum class Renderer {
  OPENGL,
  OPENGL_ES
};

struct Context
{
	bool enableDepthTest = true;
	bool enableStencilTest = false;

	int openglMajor = 3;
	int openglMinor = 3;
	int coreProfile = true;
	int forwardCompatible = false;

	Renderer renderer = Renderer::OPENGL;
};

} // namespace ogl
