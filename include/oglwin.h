#pragma once

#include "context.h"
#include <string>

namespace ogl {

enum class Key
{
	SPACE =             32,
	APOSTROPHE =        39,
	PLUS =              43,
	COMMA =             44,
	MINUS =             45,
	PERIOD =            46,
	SLASH =             47,
	_0 =                48,
	_1 =                49,
	_2 =                50,
	_3 =                51,
	_4 =                52,
	_5 =                53,
	_6 =                54,
	_7 =                55,
	_8 =                56,
	_9 =                57,
	SEMICOLON =         58,
	EQUAL =             61,
	A =                 65,
	B =                 66,
	C =                 67,
	D =                 68,
	E =                 69,
	F =                 70,
	G =                 71,
	H =                 72,
	I =                 73,
	J =                 74,
	K =                 75,
	L =                 76,
	M =                 77,
	N =                 78,
	O =                 79,
	P =                 80,
	Q =                 81,
	R =                 82,
	S =                 83,
	T =                 84,
	U =                 85,
	V =                 86,
	W =                 87,
	X =                 88,
	Y =                 89,
	Z =                 90,
	LEFT_BRACKET =      91,
	BACKSLASH =         92,
	RIGHT_BRACKET =     93,
	a =                 97,
	b =                 98,
	c =                 99,
	d =                 100,
	e =                 101,
	f =                 102,
	g =                 103,
	h =                 104,
	i =                 105,
	j =                 106,
	k =                 107,
	l =                 108,
	m =                 109,
	n =                 110,
	o =                 111,
	p =                 112,
	q =                 113,
	r =                 114,
	s =                 115,
	t =                 116,
	u =                 117,
	v =                 118,
	w =                 119,
	x =                 120,
	y =                 121,
	z =                 122,
	ESCAPE,
	ENTER,
	TAB,
	BACKSPACE,
	INSERT,
	DELETE,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	PAGE_UP,
	PAGE_DOWN,
	HOME,
	END,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	UNDEFINED = 999,
};

enum class MouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	UNDEFINED = 999
};

enum class KeyState {
	PRESS,
	RELEASE
};

class WindowInterface {
public:
	virtual void onKeyboardEvent(Key, KeyState) {}
	virtual void onPassiveMouseEvent(double /*x*/, double /*y*/) {}
	virtual void onRenderSceneEvent() {}
	virtual void onMouseEvent(MouseButton, KeyState, double /*x*/, double /*y*/) {}
	virtual void onResizeEvent(int /*width*/, int /*height*/) {}
};

void Initialize(int argc, char* argv[], const Context& ctx);
void CreateWindow(const std::string title, std::size_t width, std::size_t height, bool fullscreen);
void RunMainLoop(WindowInterface& callBackInterface);
void PostQuitMessage();
void Terminate();

} // namespace ogl
