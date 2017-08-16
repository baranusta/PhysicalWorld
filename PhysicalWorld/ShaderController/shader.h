#pragma once

#include "..\stdafx.h"

class Shader
{
public:
	int usedBy;
	GLuint shaderProgram;
	Shader(GLuint shaderProg) :
		shaderProgram(shaderProg), usedBy(1)
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