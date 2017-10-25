#include "fluid_renderer.h"

render_engine::FluidRenderer::FluidRenderer()
	:Renderer(), m_shader("Render\\common.vs","Render\\Renderers\\default_fluid.fs")
{
	glUseProgram(m_shader.getProgId());
	m_cam_matrix = glGetUniformLocation(m_shader.getProgId(), "mat_projView");
	m_cam_inv_matrix = glGetUniformLocation(m_shader.getProgId(), "mat_inv_projView");
	m_screenSize = glGetUniformLocation(m_shader.getProgId(), "screenSize");
	m_camPos = glGetUniformLocation(m_shader.getProgId(), "camPos");
	m_camNearFar = glGetUniformLocation(m_shader.getProgId(), "camNearFar"); 

}

render_engine::FluidRenderer::FluidRenderer(std::string vShader, std::string fShader)
	:m_shader(vShader, fShader)
{
	glUseProgram(m_shader.getProgId());
	m_cam_matrix = glGetUniformLocation(m_shader.getProgId(), "mat_projView");
	m_cam_inv_matrix = glGetUniformLocation(m_shader.getProgId(), "mat_inv_projView");
	m_camNearFar = glGetUniformLocation(m_shader.getProgId(), "camNearFar");
	m_camPos = glGetUniformLocation(m_shader.getProgId(), "camPos");
	m_screenSize = glGetUniformLocation(m_shader.getProgId(), "screenSize");
}

void render_engine::FluidRenderer::draw(Camera& cam)
{
	glEnable(GL_PROGRAM_POINT_SIZE);

	glUseProgram(m_shader.getProgId());
	
	glm::mat4 projView = cam.getProjMat() * cam.getViewMat();
	glm::mat4 inv_projView = glm::inverse(projView);

	glUniformMatrix4fv(m_cam_matrix, 1, GL_FALSE, glm::value_ptr(projView));
	glUniformMatrix4fv(m_cam_inv_matrix, 1, GL_FALSE, glm::value_ptr(inv_projView));

	glUniform2f(m_camNearFar, cam.getNearFar().x, cam.getNearFar().y);
	glUniform2f(m_screenSize, cam.getSize().x, cam.getSize().y);
	glUniform3f(m_camPos, cam.getCenter().x, cam.getCenter().y, cam.getCenter().z);
	
	//Set the active Vertex array object
	glBindVertexArray(m_vao.get());
	
	//Draw
	glDrawArrays(GL_POINTS, 0, m_vao.getVertexCount());
	
	glBindVertexArray(0);
	glDisable(GL_PROGRAM_POINT_SIZE);
}
