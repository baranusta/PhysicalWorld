#pragma once

#include "..\Models\VAOs\fluid_vao.h"
#include "renderer.h"

#include "..\..\ShaderController\render_shader_controller.h"


namespace render_engine
{
	class FluidRenderer: public Renderer
	{
	private:
		RenderShaderController m_shader;
		GLuint m_screenSize;
		GLuint m_camNearFar;
		GLuint m_camPos;

	public:
		FluidRenderer();
		FluidRenderer(std::string vShader, std::string fShader);

		void draw(Camera& cam);
	};
}