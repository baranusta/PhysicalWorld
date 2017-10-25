#pragma once

#include "..\..\Models\Camera\camera.h"
#include "..\Models\VAOs\vertex_array_object.h"
#include "..\..\stdafx.h"

namespace render_engine
{
	class Renderer
	{
	protected:
		GLuint m_cam_matrix;
		GLuint m_cam_inv_matrix;
		VertexArrayObject m_vao;
		int m_count;

	public:

		template<class T>
		void setBuffer(int bufferType, GLuint buffer);

		virtual void draw(Camera& cam) = 0;

		virtual void setCount(int count)
		{
			m_count = count;
			m_vao.setVertexCount(count);
		}
	};

	template<class T>
	void Renderer::setBuffer(int bufferType, GLuint buffer)
	{
		m_vao.setBuffer<T>(bufferType, buffer);
	}
}