#version 300 es

precision highp float;
precision highp int;

in vec2 texCoords0;
uniform sampler2D myTexture;
out vec4 fragmentColor;

void main ()
{
	fragmentColor = texture2D(myTexture, texCoords0);
}
