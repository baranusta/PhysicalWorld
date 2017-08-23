#pragma once

#include "..\stdafx.h"


template<class T>
void getDataFromGPU(GLuint buffer, std::vector<T>& data)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer); // 
	GLvoid* s = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	memcpy(&data[0], s, sizeof(T) * data.size());
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}