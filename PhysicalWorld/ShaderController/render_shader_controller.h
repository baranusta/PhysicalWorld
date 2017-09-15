#pragma once

#include "shader_controller.h"


class RenderShaderController :public ShaderController
{
private:
	GLuint m_vShader, m_fShader;
	std::string fileName_V;
	std::string fileName_F;

	bool shouldRecompile;

public:
	RenderShaderController(std::string fileName_V, std::string fileName_F)
	{
		shouldRecompile = false;
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
		//This does not have to be same with compute shaders
		// for the time being I dont care if both of the shaders are recompiled.
		if (!shouldRecompile)
			return;

		attachShaders(prog);
		shouldRecompile = false;
	}

	void setMacroVS()
	{}
	void setMacroFS() 
	{}

	void markDirty()
	{
		shouldRecompile = true;
		std::cout << "Marked Dirty vs-fs";
	}

	void operator()() 
	{ 
		glUseProgram(getProgId());
	}
};



