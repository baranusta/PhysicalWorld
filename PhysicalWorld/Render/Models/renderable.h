#pragma once

#include "..\..\stdafx.h"

#include "..\..\ShaderController\render_shader_controller.h"

namespace render_engine
{
	class Renderable
	{
	protected:
		glm::vec3 m_model;

	public:
		virtual void draw() = 0;
	};
}