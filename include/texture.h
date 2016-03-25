#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filename);
        ~Texture();

	void enable(GLenum TextureUnit);
	void disable(GLenum TextureUnit);

private:
	GLuint mTexture;
	GLenum mTarget;
};

#endif // TEXTURE_H
