#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	
	//read shader file..
	std::ifstream vertexFlie;
	std::ifstream fragmentFlie;
	
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	vertexFlie.open(vertexShaderPath);
	fragmentFlie.open(fragmentShaderPath);

	vertexFlie.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFlie.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFlie.is_open() || !fragmentFlie.is_open()) {
			throw std::exception("Open File Error!");
		}

		//file switch char*...
		//file -> stringStream
		vertexSStream << vertexFlie.rdbuf();
		fragmentSStream << fragmentFlie.rdbuf();

		//stringStream -> string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
	
		//string -> char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		

		//link shader into ID..
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int id, std::string type) {

	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		
		if (!success) {
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			std::cout << "Shader Compile Error!\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "Program Compile Error!\n" << infoLog << std::endl;
		}
	}


}
