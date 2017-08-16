#pragma once

#include "..\Models\VAOs\fluid_vao.h"
#include "renderer.h"

#include "..\..\ShaderController\render_shader_controller.h"


namespace render_engine
{
	class FluidRenderer: Renderer
	{
	private:
		VertexArrayObject m_vao;
		unsigned int m_count;
		RenderShaderController m_shader;

	public:
		FluidRenderer(std::string vShader = "Render\\common.vs", 
						std::string fShader = "Render\\Renderers\\default_fluid.fs");

		void setVAO(VertexArrayObject);
		void draw();
	};
}