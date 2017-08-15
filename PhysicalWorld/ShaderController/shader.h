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

	virtual ~Shader()
	{
		glDeleteProgram(shaderProgram);
	}
};