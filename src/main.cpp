#include "oglwin.h"
#include "common.h"
#include "technique.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <iostream>
#include <array>
using namespace std;

struct MeshVertex
{
	glm::vec2 position;
	glm::vec2 textCoord0;
};

class OpenGLWindow : public ogl::WindowInterface {
public:
	OpenGLWindow (const string& filename)
		: mTexture{filename},
		  mMesh{
			   {{-0.5f,  0.5f}, {0.0f, 1.0f}},
			   {{-0.5f, -0.5f}, {0.0f, 0.0f}},
			   {{ 0.5f, -0.5f}, {1.0f, 0.0f}},
			   {{ 0.5f, -0.5f}, {1.0f, 0.0f}},
			   {{ 0.5f,  0.5f}, {1.0f, 1.0f}},
			   {{-0.5f,  0.5f}, {0.0f, 1.0f}}
			   }
	{
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		createVertexArrayObject();

		mTechnique.addShaderProgram(GL_VERTEX_SHADER, {"resources/vertexshader.glsl"});
		mTechnique.addShaderProgram(GL_FRAGMENT_SHADER, {"resources/fragmentshader.glsl"});
		mTechnique.finalize();

		mTechnique.enable();
		mTechnique.setUniform(mTechnique.getUniformLocation("myTexture"), 0);
		mTechnique.disable();
	}

	void onKeyboardEvent(ogl::Key key, ogl::KeyState keyState) override
	{
		if (key == ogl::Key::ESCAPE)
			ogl::PostQuitMessage();
	}

	void onRenderSceneEvent() override
	{
		glClear(GL_COLOR_BUFFER_BIT);

		mTexture.enable(GL_TEXTURE0);
		enableVertexArrayObject();

		glEnableVertexAttribArray(static_cast<int>(ogl::AttribPosition::position));
		glEnableVertexAttribArray(static_cast<int>(ogl::AttribPosition::textCoords0));

		mTechnique.enable();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		mTechnique.disable();

		glDisableVertexAttribArray(static_cast<int>(ogl::AttribPosition::position));
		glDisableVertexAttribArray(static_cast<int>(ogl::AttribPosition::textCoords0));
	}

	void onResizeEvent(int width, int height) override
	{
		glViewport(0, 0, width, height);
	}

private:
	void enableVertexArrayObject()
	{
		glBindVertexArray(mVertexArrayObject);
	}

	void createVertexArrayObject()
	{
		// This will identify our vertex buffer
		glGenBuffers(1, &mArrayBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, mArrayBufferObject);
		glBufferData(GL_ARRAY_BUFFER, mMesh.size() * sizeof(MeshVertex),
					 mMesh.data(), GL_DYNAMIC_DRAW);

		glGenVertexArrays(1, &mVertexArrayObject);
		glBindVertexArray(mVertexArrayObject);
		glEnableVertexAttribArray(static_cast<int>(ogl::AttribPosition::position));
		glEnableVertexAttribArray(static_cast<int>(ogl::AttribPosition::textCoords0));
		glBindBuffer(GL_ARRAY_BUFFER, mArrayBufferObject);

		glVertexAttribPointer(static_cast<int>(ogl::AttribPosition::position),
							  2, GL_FLOAT, GL_FALSE,
							  sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, position));
		glVertexAttribPointer(static_cast<int>(ogl::AttribPosition::textCoords0),
							  2, GL_FLOAT, GL_FALSE,
							  sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, textCoord0));

		glDisableVertexAttribArray(static_cast<int>(ogl::AttribPosition::position));
		glDisableVertexAttribArray(static_cast<int>(ogl::AttribPosition::textCoords0));
	}

private:
	ogl::Technique mTechnique;
	ogl::Texture mTexture;
	vector<MeshVertex> mMesh;
	GLuint mArrayBufferObject;
	GLuint mVertexArrayObject;
};

int main(int argc, char* argv[])
{
	try
	{
		ogl::Initialize(argc, argv, {} /*default context*/);
		ogl::CreateWindow("test title", 800, 600, false);

		const string imageFilename = argc == 1 ?
					"./" + string{"resources/test.dds"} : string{argv[1]};

		OpenGLWindow window(imageFilename);
		ogl::RunMainLoop(window);
		ogl::Terminate();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exc)
	{
		cerr << exc.what() << endl;
		ogl::Terminate();
		return EXIT_FAILURE;
	}
}
