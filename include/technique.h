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

	Technique& addShaderProgram(GLenum type, const std::string& filename);

	Technique& finalize();

	Technique& enable();
	Technique& disable();

	GLint getUniformLocation(const std::string& uniformName);
	Technique& setUniform(GLint location, GLint value);
	Technique& setUniform(GLint location, glm::mat4 mat);

private:
	void deleteShaders();
	std::string getTextFromFile(const std::string& filename);

private:
	GLint mProgramID;
	std::vector<GLint> mShaders;
	std::map<std::string, GLuint> mUniformLocationMap;
};

}
