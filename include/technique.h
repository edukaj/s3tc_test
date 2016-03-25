#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <string>
#include <vector>
#include <GL/glew.h>

class Technique {
public:
	Technique();
	~Technique();

	void addShaderProgram(GLenum type, const std::string& filename);

	void finalize();

	void enable();
	void disable();

	GLint getUniformLocation(const std::string& uniformName);
	void setVertexLocation(const std::string& attribName, GLint attribLocation);
	void setUniform(GLint location, GLint value);

private:
	void deleteShaders();
	std::string getTextFromFile(const std::string& filename);

private:
	GLint mProgramID;
	std::vector<GLint> mShaders;
};


#endif // TECHNIQUE_H
