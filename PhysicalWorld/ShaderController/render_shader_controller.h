#pragma once

#include "shader_controller.h"


class RenderShaderController :public ShaderController
{
private:
	GLuint m_vShader, m_fShader;
	std::string fileName_V;
	std::string fileName_F;

public:
	RenderShaderController(std::string fileName_V, std::string fileName_F)
	{
		this->fileName_V = fileName_V;
		this->fileName_F = fileName_F;
		std::string name = fileName_V + fileName_F;
		createShader(name);
	}

	virtual void attachShaders(GLuint prog)
	{
		GLuint vertex_shader = compile(GL_VERTEX_SHADER, fileName_V);
		GLuint fragment_shader = compile(GL_FRAGMENT_SHADER, fileName_F);
		glAttachShader(prog, vertex_shader);
		glAttachShader(prog, fragment_shader);

		glLinkProgram(prog);

		glDetachShader(prog, vertex_shader);
		glDetachShader(prog, fragment_shader);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

	}

	void recompile(GLuint prog)
	{
	}

	void setMacroVS()
	{}
	void setMacroFS() 
	{}

	void operator()() 
	{ 
		glUseProgram(getProgId());
	}
};



