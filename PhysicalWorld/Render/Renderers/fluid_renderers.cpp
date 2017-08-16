#include "fluid_renderer.h"

render_engine::FluidRenderer::FluidRenderer(std::string vShader, std::string fShader)
	:m_shader(vShader, fShader)
{

}

void render_engine::FluidRenderer::setVAO(VertexArrayObject vao)
{
	m_vao = vao;
}

void render_engine::FluidRenderer::draw()
{
	glUseProgram(m_shader.getProgId());

	//Set the active Vertex array object
	glBindVertexArray(m_vao.get());

	//Draw
	glDrawArrays(GL_POINTS, 0, m_vao.getVertexCount());
}
