#pragma once
#pragma once

#include "shader_controller.h"


class ComputeShaderController :public ShaderController
{
private:
	std::string fileName_C;

public:
	ComputeShaderController(std::string fileName_C)
	{
		this->fileName_C = fileName_C;
		createShader(fileName_C);

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
	}

	virtual void attachShaders(GLuint prog)
	{
		GLuint compute_shader = compile(GL_COMPUTE_SHADER, fileName_C);
		glAttachShader(prog, compute_shader);

		glLinkProgram(prog);

		glDetachShader(prog, compute_shader);

		glDeleteShader(compute_shader);

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
	}

	void dispatch(unsigned int xSize, unsigned int ySize, unsigned int zSize)
	{
		glDispatchCompute(xSize, ySize, zSize);
	}
};



