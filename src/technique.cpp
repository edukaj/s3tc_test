#include "technique.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ogl;

Technique::Technique() : mProgramID(glCreateProgram())
{
	if(mProgramID == 0)
		throw runtime_error{"unable to create glsl program"};
}

Technique::~Technique()
{
	deleteShaders();
	glDeleteProgram(mProgramID);
}

void Technique::addShaderProgram(GLenum type, const string &filename)
{
	GLint shaderID = glCreateShader (type);
	const auto shaderSource = getTextFromFile(filename);
	const GLchar* data = shaderSource.c_str();

	glShaderSource (shaderID, 1, &data, nullptr);
	glCompileShader (shaderID);

	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		string errorLog(maxLength, ' ');
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		ostringstream os;
		os << "Unable to build " << filename << '\n'
		   << errorLog << "\nShader source:\n" << shaderSource;
		throw runtime_error(os.str());
	}

	mShaders.push_back(shaderID);
}

void Technique::finalize()
{
	for(auto shader : mShaders)
		glAttachShader(mProgramID, shader);

	glLinkProgram (mProgramID);

	GLint success = 0;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		string infoLog(maxLength, ' ');
		glGetProgramInfoLog(mProgramID, maxLength, &maxLength, &infoLog[0]);

		ostringstream os;
		os << "Unable to link program:\n" << infoLog;

		throw runtime_error(os.str());
	}

	glValidateProgram(mProgramID);
	glGetProgramiv(mProgramID, GL_VALIDATE_STATUS, &success);
	if (!success) {
		GLint maxLength = 0;
		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		string infoLog(maxLength, ' ');
		glGetProgramInfoLog(mProgramID, maxLength, &maxLength, &infoLog[0]);

		ostringstream os;
		os << "Unable to validate program:\n" << infoLog;

		throw runtime_error(os.str());
	}

	deleteShaders();
}

void Technique::enable()
{
	glUseProgram(mProgramID);
}

void Technique::disable()
{
	glUseProgram(0);
}

GLint Technique::getUniformLocation(const string &uniformName)
{
	GLint location = glGetUniformLocation(mProgramID, uniformName.c_str());

	if(location == -1)
	{
		ostringstream os;
		os << "Unable to locate:" << uniformName << " uniform location";
		throw runtime_error(os.str());
	}
	return location;
}

void Technique::setVertexLocation(const string &attribName, GLint attribLocation)
{
	glBindAttribLocation(mProgramID, attribLocation, attribName.c_str());
}

void Technique::setUniform(GLint location, GLint value)
{
	glUniform1i(location, value);
}

void Technique::deleteShaders()
{
	for(auto shaderID : mShaders)
		glDeleteShader(shaderID);
	mShaders.clear();
}

string Technique::getTextFromFile(const string &filename)
{
	ifstream file(filename);

	if(!file)
	{
		ostringstream os;
		os << "Unable to open shader " << filename;
		throw runtime_error(os.str());
	}

	ostringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

