#include "vertex_array_object.h"



render_engine::VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &element_array_handle);
	glBindVertexArray(vao);
}

render_engine::VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vao);
	for (auto pair : buffers)
	{
		glDeleteBuffers(1, &pair.second);
	}
	glDeleteBuffers(1, &element_array_handle);
}

int render_engine::VertexArrayObject::getVertexCount()
{
	return m_vertexCount;
}

void render_engine::VertexArrayObject::setVertexCount(int vertexCount)
{
	m_vertexCount = vertexCount;
}


void render_engine::VertexArrayObject::setElementArray(std::vector<int> indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0],
		GL_STATIC_DRAW);
}
