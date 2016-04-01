#version 330

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 textCoords0;

uniform mat4 camera;
uniform mat4 model;

out vec2 fragTexCoords0;

void main()
{
	gl_Position = camera * model * vertexPosition;
	fragTexCoords0 = textCoords0;
}
