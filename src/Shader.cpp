#include "Shader.h"


Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
	this->vertexFile = vertexFile;
	this->fragmentFile = fragmentFile;
}
Shader::~Shader(){
	glDetachShader(shaderProgram, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

// Sets up the shader
void Shader::setupShaders()
{
	vertexShader = loadShader(std::string(GLSL_FILE_PATH) + vertexFile, GL_VERTEX_SHADER);
	shaderCompileCheck(vertexShader);
	fragmentShader = loadShader(std::string(GLSL_FILE_PATH) + fragmentFile, GL_FRAGMENT_SHADER);
	shaderCompileCheck(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	shaderLinkCheck(shaderProgram);
	glValidateProgram(shaderProgram);
}


// Get GetAttribLocation
GLint Shader::getAttribLocation(std::string name)
{
	GLint attrib = -1;
	const GLchar * charName = name.c_str();
	attrib = glGetAttribLocation(shaderProgram, charName);

	return attrib;
}

// Gets UniformLocation
GLint Shader::getUniformLocation(std::string name)
{
	GLint uniform = -1;
	const GLchar * charName = name.c_str();
	uniform = glGetUniformLocation(shaderProgram, charName);

	return uniform;
}

// Call with true to start use, false to stop use
void Shader::useProgram(bool isUsed)
{
	if(isUsed)
		glUseProgram(shaderProgram);
	else
		glUseProgram(0);
}


void Shader::releaseResources()
{
	glDetachShader(shaderProgram, vertexShader);
	glDeleteShader(vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);

}

// Loads the shader from file
int Shader::loadShader(std::string file, GLint type)
{
	int shaderID = 0;
	std::ifstream infile(file.c_str());
	if(infile.is_open())
	{
		const char * src;
		int length;
		std::string srcLine, srcLines;
		while(!infile.eof())
		{
			getline(infile, srcLine);
			srcLines += srcLine + "\n";
		}
		infile.close();

		shaderID = glCreateShader(type);
		src = srcLines.c_str();
		length = srcLines.size();
		glShaderSource(shaderID, 1, &src, &length);
		glCompileShader(shaderID);
	}else {
		std::cout << file << " not found" ;
	}

	return shaderID;
}

// Compile the shader
bool Shader::shaderCompileCheck(GLuint shaderID)
{
	GLint isCompiled = 0;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
		std::cerr << &infoLog[0] << "     COMPILE ERROR!";
		return false;
	}

	return true;
}

// Checks the link
bool Shader::shaderLinkCheck(GLuint programID)
{
	GLint isLinked = 0;

	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		std::cerr << &infoLog[0] << "     LINK ERROR!";
		return false;
	}

	return true;
}
