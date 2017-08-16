#include "fluid_renderer.h"

render_engine::FluidRenderer::FluidRenderer()
	:m_shader("Render\\common.vs","Render\\Renderers\\default_fluid.fs")
{
}

render_engine::FluidRenderer::FluidRenderer(std::string vShader, std::string fShader)
	:m_shader(vShader, fShader)
{

}


render_engine::VertexArrayObject * render_engine::FluidRenderer::getVAO()
{
	return &m_vao;
}

void render_engine::FluidRenderer::setParticleCount(int count)
{
	m_vao.setVertexCount(count);
}

void render_engine::FluidRenderer::draw()
{
	glEnable(GL_PROGRAM_POINT_SIZE);

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	glUseProgram(m_shader.getProgId());
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}

	//Set the active Vertex array object
	glBindVertexArray(m_vao.get());
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	
	//Draw
	glDrawArrays(GL_POINTS, 0, m_vao.getVertexCount());
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	glBindVertexArray(0);
	glDisable(GL_PROGRAM_POINT_SIZE);
}
