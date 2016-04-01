#pragma once
#include "oglwin.h"
#include "common.h"
#include "technique.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <string>

class TextureTestWindow : public ogl::WindowInterface {
public:
	TextureTestWindow (const std::string& filename);

	void onKeyboardEvent(ogl::Key key, ogl::KeyState keyState) override;
	void onRenderSceneEvent() override;
	void onResizeEvent(int width, int height) override;

private:
	void enableVertexArrayObject();

	void createPositionAndTextCoordsBufferObjects();
	void createVertexArrayObject();

	void mapPositionVertex();
	void mapTextCoords0Vertex();

private:
	ogl::Technique mTechnique;
	ogl::Texture mTexture;
	GLuint mArrayBufferObject;
	GLuint mPositionBuffer;
	GLuint mTextCoords0Buffer;

	std::vector<glm::vec2> mPositions;
	std::vector<glm::vec2> mTextCoords;
};
