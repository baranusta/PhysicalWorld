#pragma once

#include "..\..\..\stdafx.h"

#define BUF_POSITION 0
#define BUF_NORMAL  1

namespace render_engine
{
	class VertexArrayObject
	{
		GLuint vao;
		GLuint element_array_handle;

	protected:
		int m_vertexCount;
		std::unordered_map<int, GLuint> buffers;

	public:
		VertexArrayObject();
		~VertexArrayObject();

		GLuint get()
		{
			return vao;
		}

		int getVertexCount();
		void setVertexCount(int vertexCount);
		
		//bufferType should be one of the defined values
		//since they also used for binding index
		template <class T>
		void setData(int bufferType, std::vector<T> data);

		template<typename T>
		void setBuffer(int bufferType, GLuint buffer);

		void setElementArray(std::vector<int> indices);
	};
}

template<typename T>
void render_engine::VertexArrayObject::setBuffer(int bufferType, GLuint buffer)
{

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	glBindVertexArray(vao);
	if (buffers.find(bufferType) == buffers.end())
	{
		buffers[bufferType] = buffer;
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(bufferType, sizeof(T) / sizeof(float), GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(bufferType);

	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	glBindVertexArray(0);
}


template<class T>
inline void render_engine::VertexArrayObject::setData(int bufferType, std::vector<T> data)
{
	glBindVertexArray(vao);
	GLuint buffer = buffers.find(bufferType);
	if (buffer == buffers.end())
	{
		glGenBuffers(1, buffer);
		buffers[bufferType] = buffer;
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(bufferType, sizeof(T) / sizeof(float), GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(bufferType);

	glBindVertexArray(0);
}