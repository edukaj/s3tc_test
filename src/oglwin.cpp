#include "oglwin.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
using namespace ogl;
using namespace std;


GLFWwindow* g_GLFW_Window = nullptr;
WindowInterface* g_Window = nullptr;

std::map<GLFWwindow*, WindowInterface*> g_WindowMap;

Context g_Context;

Key fromGLFWKey(int k)
{
	if (k >= GLFW_KEY_SPACE && k <= GLFW_KEY_RIGHT_BRACKET)
		return (Key)k;

	switch (k)
	{
	case GLFW_KEY_ESCAPE: return Key::ESCAPE;
	case GLFW_KEY_ENTER: return Key::ENTER;
	case GLFW_KEY_TAB: return Key::TAB;
	case GLFW_KEY_BACKSPACE: return Key::BACKSPACE;
	case GLFW_KEY_INSERT: return Key::INSERT;
	case GLFW_KEY_DELETE: return Key::DELETE;
	case GLFW_KEY_RIGHT: return Key::RIGHT;
	case GLFW_KEY_LEFT: return Key::LEFT;
	case GLFW_KEY_DOWN: return Key::DOWN;
	case GLFW_KEY_UP: return Key::UP;
	case GLFW_KEY_PAGE_UP: return Key::PAGE_UP;
	case GLFW_KEY_PAGE_DOWN: return Key::PAGE_DOWN;
	case GLFW_KEY_HOME: return Key::HOME;
	case GLFW_KEY_END: return Key::END;
	case GLFW_KEY_F1: return Key::F1;
	case GLFW_KEY_F2: return Key::F2;
	case GLFW_KEY_F3: return Key::F3;
	case GLFW_KEY_F4: return Key::F4;
	case GLFW_KEY_F5: return Key::F5;
	case GLFW_KEY_F6: return Key::F6;
	case GLFW_KEY_F7: return Key::F7;
	case GLFW_KEY_F8: return Key::F8;
	case GLFW_KEY_F9: return Key::F9;
	case GLFW_KEY_F10: return Key::F10;
	case GLFW_KEY_F11: return Key::F11;
	case GLFW_KEY_F12: return Key::F12;
	default: throw runtime_error{"Unimplemented key"};
	}
}

MouseButton fromGLFWMouseButton(int button)
{
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::LEFT;
	case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::RIGHT;
	case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::MIDDLE;
	default: throw runtime_error{"Unimplemented mouse button"};
	}
}

KeyState fromGLFWKeyState(int state)
{
	switch (state) {
	case GLFW_PRESS: return KeyState::PRESS;
	case GLFW_RELEASE: return KeyState::RELEASE;
	default: runtime_error{"Unimplemented key state"};
  }
}

void GLFWKeyCallback(GLFWwindow*, int key, int, int action, int)
{
	auto k = fromGLFWKey(key);
	auto state = fromGLFWKeyState(action);


	g_Window->onKeyboardEvent(k, state);
}


void GLFWCursorPosCallback(GLFWwindow*, double x, double y)
{
	g_Window->onPassiveMouseEvent(x, y);
}


void GLFWMouseButtonCallback(GLFWwindow*, int button, int action, int)
{
	MouseButton mouseButton = fromGLFWMouseButton(button);
	KeyState state = fromGLFWKeyState(action);

	double x, y;
	glfwGetCursorPos(g_GLFW_Window, &x, &y);

	g_Window->onMouseEvent(mouseButton, state, x, y);
}

void GLFWResizeCallback(GLFWwindow*, int width, int height)
{
	g_Window->onResizeEvent(width, height);
}

static void GLFWInitCallbacks()
{
	glfwSetKeyCallback(g_GLFW_Window, GLFWKeyCallback);
	glfwSetCursorPosCallback(g_GLFW_Window, GLFWCursorPosCallback);
	glfwSetMouseButtonCallback(g_GLFW_Window, GLFWMouseButtonCallback);
	glfwSetWindowSizeCallback(g_GLFW_Window, GLFWResizeCallback);
}

void GLFWErrorCallback(int error, const char* description)
{
  ostringstream os;
  os << "GLFW error: " << error << " - " << description;
  throw runtime_error{os.str()};
}

namespace ogl {

void setContextSettings(const Context& ctx)
{
	g_Context = ctx;


	if (g_Context.renderer == Renderer::OPENGL)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, g_Context.forwardCompatible);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	}
	else
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, g_Context.openglmajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, g_Context.openglMinor);


#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

}

void Initialize(int argc, char *argv[], const Context &ctx)
{

	if(!glfwInit())
		throw std::runtime_error{"Unable to initalize glfw"};

	glfwSetErrorCallback(GLFWErrorCallback);

	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);

	setContextSettings(ctx);

	cout << "GLFW " << major << '.' << minor << '.' << rev << " initialized" << endl;
}


void CreateWindow(const string title, size_t width, size_t height, bool fullscreen)
{
	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

	g_GLFW_Window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);

	if (!g_GLFW_Window)
		throw runtime_error{"Unable to create main window"};

	glfwMakeContextCurrent(g_GLFW_Window);

	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK)
		throw runtime_error{(const char*)glewGetErrorString(res)};

	cout << "Renderer: " << glGetString (GL_RENDERER) << '\n'
		 << "OpenGL Version: " << glGetString (GL_VERSION)
		 << endl;
}

void RunMainLoop(WindowInterface& window)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (g_Context.enableDepthTest)
	{
		cout << "Enabling depth test" << endl;
//		glEnable(GL_DEPTH_TEST);
	}

	g_Window = &window;
	GLFWInitCallbacks();

	while (!glfwWindowShouldClose(g_GLFW_Window))
	{
		g_Window->onRenderSceneEvent();
		glfwSwapBuffers(g_GLFW_Window);
		glfwPollEvents();
	}
}

void Terminate()
{
	glfwDestroyWindow(g_GLFW_Window);
	glfwTerminate();
}

void PostQuitMessage()
{
	glfwSetWindowShouldClose(g_GLFW_Window, GL_TRUE);
}

} // namespace ogl

/*
class MyWindows : public CallbacksInterface
{
public:
  void onKeyboardEvent(Key key, KeyState keyState = KeyState::PRESS)
  {

  };

  void onPassiveMouseEvent(int x, int y)
  {

  };

  void onRenderSceneEvent()
  {

  };

  void onMouseEvent(MouseButton button, y state, int x, int y) {};
private:

}

int main(int argc, char* argv[])
{

  try
  {
	ogl::Initialize(argc, argv);
	MyWindows myWindow;
	ogl::RunMainLoop(myWindow);
	ogl::Terminate();

}
*/
