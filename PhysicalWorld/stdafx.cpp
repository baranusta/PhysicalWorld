#include "stdafx.h"


void foo()
{
	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}

}