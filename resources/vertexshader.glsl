#version 330

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 textureCoordinates;

out vec2 textureCoordinates0;

void main()
{
	gl_Position = vec4 (vertexPosition, 0.0, 1.0);
	textureCoordinates0 = textureCoordinates;
}
