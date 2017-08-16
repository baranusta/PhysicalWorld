#pragma once

#include "..\Models\VAOs\fluid_vao.h"
#include "renderer.h"

#include "..\..\ShaderController\render_shader_controller.h"


namespace render_engine
{
	class FluidRenderer: public Renderer
	{
	private:
		VertexArrayObject m_vao;
		unsigned int m_count;
		RenderShaderController m_shader;

	public:
		FluidRenderer();
		FluidRenderer(std::string vShader, std::string fShader);

		VertexArrayObject* getVAO();
		void setParticleCount(int count);
		void draw();
	};
}