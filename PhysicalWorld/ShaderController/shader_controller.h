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

	void appendMacros(std::string& source, const std::unordered_map<std::string, std::string>& macros);

	GLuint compile(GLuint type, std::string fileName, const std::unordered_map<std::string, std::string>& macros = {});

	virtual void attachShaders(GLuint) = 0;
	virtual void recompile(GLuint) = 0;

	void createShader(std::string name);

public:
	ShaderController()
	{

	}

	~ShaderController() 
	{
		if (shaders.find(m_name) != shaders.end())
		{
			if (shaders[m_name]->usedBy == 1)
			{
				glDeleteProgram(shaders[m_name]->shaderProgram);
				delete shaders[m_name];
				shaders.erase(m_name);
			}
			else
				shaders[m_name]->usedBy--;
		}
	}

	GLuint getProgId() 
	{ 
		recompile(shaders[m_name]->shaderProgram);
		return shaders[m_name]->shaderProgram; 
	}

};