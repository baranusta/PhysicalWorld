#pragma once
#pragma once

#include "shader_controller.h"


class ComputeShaderController :public ShaderController
{
private:
	std::string fileName_C;

	bool shouldRecompile;
	std::unordered_map<std::string, std::string> macros;

	void linkShader(GLuint progId, GLuint shaderId)
	{
		glAttachShader(progId, shaderId);

		glLinkProgram(progId);

		glDetachShader(progId, shaderId);

		glDeleteShader(shaderId);
	}

public:
	ComputeShaderController(std::string fileName_C)
	{
		this->fileName_C = fileName_C;
		setMacro("THREAD_COUNT_X", 1);
		createShader(fileName_C);

	}

	virtual void attachShaders(GLuint prog)
	{
		GLuint compute_shader = compile(GL_COMPUTE_SHADER, fileName_C, macros); 
		linkShader(prog, compute_shader);
	}

	void dispatch(unsigned int xSize, unsigned int ySize, unsigned int zSize)
	{
		glDispatchCompute(xSize, ySize, zSize);
	}

	void recompile(GLuint prog)
	{
		if (!shouldRecompile)
			return;

		attachShaders(prog);
		shouldRecompile = false;
	}

	void setMacro(std::string name, std::string value)
	{
		if (macros.find(name) == macros.end() || macros[name] != value)
		{
			macros[name] = value;
			shouldRecompile = true;
		}
	}

	void setMacro(std::string name, int value)
	{
		setMacro(name, std::to_string(value));
	}

	void unsetMacro(std::string name)
	{
		if (macros.find(name) != macros.end())
		{
			macros.erase(name);
			shouldRecompile = true;
		}
	}

	void markDirty()
	{
		shouldRecompile = true;
		std::cout << "Marked Dirty";
	}
};



