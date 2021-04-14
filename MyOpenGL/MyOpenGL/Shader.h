#pragma once
#include <string>

class Shader
{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		const char* vertexSource;
		const char* fragmentSource;

		unsigned int ID; //shader program id

		void use();

	private:
		std::string vertexString;
		std::string fragmentString;

		void checkCompileErrors(unsigned int id,std::string type);
};

