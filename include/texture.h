#pragma once

#include <GL/glew.h>
#include <string>

namespace ogl {

class Texture {
public:
	Texture() {}
	Texture(const std::string& filename);
	~Texture();

	void load(const std::string filename);

	void enable(GLenum TextureUnit);
	void disable(GLenum TextureUnit);

private:
	GLuint mTexture = -1;
	GLenum mTarget = -1;
};

} // namespace ogl
