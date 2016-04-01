#version 300 es

precision highp float;
precision highp int;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 inTextCoords0;

out vec2 texCoords0;

void main()
{
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	texCoords0 = inTextCoords0;
}
