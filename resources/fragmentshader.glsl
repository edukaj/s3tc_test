#version 330

in vec2 texCoords0;
uniform sampler2D myTexture;
out vec4 fragmentColor;

void main ()
{
	fragmentColor = texture2D(myTexture, texCoords0);
}
