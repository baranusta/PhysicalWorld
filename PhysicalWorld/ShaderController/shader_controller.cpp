#include "shader_controller.h"

std::unordered_map<std::string, Shader*> ShaderController::shaders = {};

std::string ShaderController::readFile(std::string fileName)

{
#ifndef NTEST
	fileName = "..\\PhysicalWorld\\" + fileName;
#endif
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::string a("Lol wrong filepath: " + fileName);
		throw a;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void ShaderController::appendMacros(std::string & source, const std::unordered_map<std::string, std::string>& macros)
{
	std::string macrosText = "";
	for (auto item : macros)
	{
		macrosText += "#define " + item.first + " " + item.second + "\n";
	}
	source = source.substr(source.find("#version"), source.find("\n") + 1) +
		macrosText +
		source.substr(source.find("\n"), source.length());
}

GLuint ShaderController::compile(GLuint type, std::string fileName, const std::unordered_map<std::string, std::string>& macros)
{
	std::string source = readFile(fileName);
	appendMacros(source, macros);
	const char * c_source = source.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &c_source, nullptr);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log(length, ' ');
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		std::cout << fileName << " " << log;
		throw std::logic_error(log);
	}
	return shader;
}

void ShaderController::createShader(std::string name)

{
	if (shaders.find(name) == shaders.end())
	{
		GLuint prog = glCreateProgram();
		attachShaders(prog);

		GLint linkSuccessful;
		glGetProgramiv(prog, GL_LINK_STATUS, &linkSuccessful);

		// If it didn't, then read and print the link log
		if (!linkSuccessful) {
			GLint logLength;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> logBuffer(logLength);
			glGetProgramInfoLog(prog, logLength, nullptr, logBuffer.data());

			std::cout << logBuffer.data();
			throw std::logic_error(logBuffer.data());
		}
		shaders.insert({ name, new Shader(prog) });
	}
	else
		shaders[name]->usedBy++;
	m_name = name;
}