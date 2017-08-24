#pragma once

#include "shader.h"

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class ShaderController {


private:
	static std::unordered_map<std::string, Shader*> shaders;
	static std::string currentlyUsedName;


protected:

	std::string m_name;

	std::string readFile(std::string fileName)
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

	GLuint compile(GLuint type, std::string fileName)
	{
		std::string source = readFile(fileName);
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
			std::cout <<fileName << " " << log;
			throw std::logic_error(log);
		}
		return shader;
	}

	virtual void attachShaders(GLuint) = 0;

	void createShader(std::string name)
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
			shaders.insert({ name, new Shader(prog)});		
		}
		else
			shaders[name]->usedBy++;
		m_name = name;
	}

public:
	ShaderController()
	{

	}
	

	GLuint getProgId() { return shaders[m_name]->shaderProgram; }

	~ShaderController() 
	{
		if (shaders.find(m_name) != shaders.end())
		{
			if (shaders[m_name]->usedBy == 1)
			{
				delete shaders[m_name];
				shaders.erase(m_name);
			}
			else
				shaders[m_name]->usedBy--;
		}
	}
};