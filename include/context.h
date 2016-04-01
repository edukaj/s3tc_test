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

	int openglmajor = 3;
	int openglMinor = 0;
	int coreProfile = true;
	int forwardCompatible = false;

	Renderer renderer = Renderer::OPENGL_ES;
};

} // namespace ogl
