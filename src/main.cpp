#include "technique.h"
#include "texture.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>
using namespace std;

void key_callback(GLFWwindow* window, int key, int, int action, int);
void resize_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initializeWindow(int glMajorVersione, int glMinorVersion);
void initalizeOpenGL();
void createVAO();

unique_ptr<Technique> g_Technique;
unique_ptr<Texture> g_Texture;
GLuint g_VAO;

int g_Width = 1280;
int g_Height = 720;

const string g_ResourcePath = "./";

vector<string> g_ExtensionList;


GLFWwindow* initializeWindow(int width = 1280, int height = 720, bool fullscreen = false,
							 int glMajorVersione = 3,
							 int glMinorVersion = 3)
{
	g_Width = width;
	g_Height = height;

	if(!glfwInit())
		throw std::runtime_error{"unable to initalize glfw"};

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersione);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(g_Width, g_Height, "test", (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

	if (window == nullptr)
		throw std::runtime_error{"unable to create window"};

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, resize_callback);

	glfwMakeContextCurrent(window);

	return window;
}

void initOpenGLExtensions()
{
	int openGLExtensionCount = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &openGLExtensionCount);

	g_ExtensionList.erase(begin(g_ExtensionList), end(g_ExtensionList));
	g_ExtensionList.reserve(openGLExtensionCount);

	for (int i = 0; i < openGLExtensionCount; ++i)
		g_ExtensionList.push_back((const char*)glGetStringi(GL_EXTENSIONS, i));
}

bool doesExtensionExist(const string& name)
{
	return find(
				begin(g_ExtensionList), end(g_ExtensionList), name) != end(g_ExtensionList);
}

void printOpenGLExtensions()
{
	cout << "OpenGL extensions" << endl;

	for (int i = 0; i < g_ExtensionList.size(); i += 2)
	{
		 cout << setw(45) << g_ExtensionList[i];
		 if (i + 1 < g_ExtensionList.size() )
			 cout << " | " << g_ExtensionList[i + 1] << endl;
		 else
			 cout << endl;
	}
}

void initalizeOpenGL()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		throw std::runtime_error{"unable to initialize glew"};

	GLint maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	cout << "Renderer: " << glGetString (GL_RENDERER) << '\n'
	   << "OpenGL Version: " << glGetString (GL_VERSION) << '\n'
	   << "Max texture size is: " << maxTextureSize << 'x' << maxTextureSize
	   << endl;

	initOpenGLExtensions();
	printOpenGLExtensions();

	if (doesExtensionExist("GL_EXT_texture_compression_s3tc"))
		cout << "GL_EXT_texture_compression_s3tc exist" << endl;
	else
		cerr << "GL_EXT_texture_compression_s3tc DOES NOT exist" << endl;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	g_Technique = make_unique<Technique>();
	g_Technique->addShaderProgram(GL_VERTEX_SHADER, g_ResourcePath + string{"resources/vertexshader.glsl"});
	g_Technique->addShaderProgram(GL_FRAGMENT_SHADER, g_ResourcePath + string{"resources/fragmentshader.glsl"});
	g_Technique->finalize();
	g_Technique->enable();

	g_Technique->enable();
	g_Technique->setVertexLocation("vertexPosition", 0);
	g_Technique->setVertexLocation("textureUVCoordinates", 1);

	g_Technique->setUniform(
				g_Technique->getUniformLocation("myTexture"), 0);
}

void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow*, int width, int height)
{
	g_Width = width;
	g_Height = height;
	glViewport(0, 0, g_Width, g_Height);
}

struct MeshVertex
{
	glm::vec2 position;
	glm::vec2 textCoord;
};

void createVAO()
{
	MeshVertex vertexes[] =
	{
		{{-1.0f,  1.0f}, {0.0f, 1.0f}},
		{{-1.0f, -1.0f}, {0.0f, 0.0f}},
		{{ 1.0f, -1.0f}, {1.0f, 0.0f}},

		{{ 1.0f, -1.0f}, {1.0f, 0.0f}},
		{{ 1.0f,  1.0f}, {1.0f, 1.0f}},
		{{-1.0f,  1.0f}, {0.0f, 1.0f}},
	};

	// This will identify our vertex buffer
	GLuint vertexbufferObject;
	glGenBuffers(1, &vertexbufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glGenVertexArrays(1, &g_VAO);
	glBindVertexArray(g_VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferObject);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, textCoord));
}

void drawTexture()
{
	g_Texture->enable(GL_TEXTURE0);

	g_Technique->enable();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	g_Technique->disable();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(g_VAO);
	drawTexture();
}

void createTexture(const string imageFilename)
{
	g_Texture = make_unique<Texture>(imageFilename);
}

int main(int argc, char* argv[])
{
	const string imageFilename = argc == 1 ?
				g_ResourcePath + string{"resources/mf_monster_minions.dds"} : string{argv[1]};

	try
	{
		auto window = initializeWindow();
		initalizeOpenGL();
		createVAO();
		createTexture(imageFilename);

		while (!glfwWindowShouldClose(window))
		{
			draw();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
	}
	catch(exception& exc)
	{
		cerr << exc.what() << endl;
		glfwTerminate();
	}

	return 0;
}
