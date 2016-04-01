#version 330

uniform sampler2D tex0;

in vec2 fragTexCoords0;
out vec4 fragmentColor;

void main ()
{
	fragmentColor = texture2D(tex0, fragTexCoords0);
}
