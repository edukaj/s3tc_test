#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

namespace ogl {

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
	void setUniform(GLint location, glm::mat4 mat);

private:
	void deleteShaders();
	std::string getTextFromFile(const std::string& filename);

private:
	GLint mProgramID;
	std::vector<GLint> mShaders;
	std::map<std::string, GLuint> mUniformLocationMap;
};

}
