#pragma once

#include "..\..\Models\Camera\camera.h"
#include "..\..\stdafx.h"

namespace render_engine
{
	class Renderer
	{
	protected:
		GLuint m_cam_matrix;

	public:
		virtual void draw(Camera& cam) = 0;
	};
}