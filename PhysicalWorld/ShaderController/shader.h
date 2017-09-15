#pragma once

#include "..\stdafx.h"

class ShaderController;

class Shader
{
public:
	int usedBy;
	ShaderController* m_shader;
	GLuint shaderProgram;
	
	Shader(GLuint shaderProg, ShaderController* shader) :
		shaderProgram(shaderProg), usedBy(1), m_shader(shader)
	{}

	Shader() :
		usedBy(0)
	{}

	Shader(const Shader& s)
		:usedBy(s.usedBy), shaderProgram(s.shaderProgram)
	{

	}

	virtual ~Shader()
	{
		glDeleteProgram(shaderProgram);
	}
};