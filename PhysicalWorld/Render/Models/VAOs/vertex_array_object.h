#pragma once

#include "..\..\..\stdafx.h"

#define VERTICE 0
#define NORMAL  1

namespace render_engine
{
	class VertexArrayObject
	{
		GLuint vao;
		GLuint element_array_handle;
		bool isElmArrayUsed;

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
		void setElementArray(std::vector<int> indices);
	};
}