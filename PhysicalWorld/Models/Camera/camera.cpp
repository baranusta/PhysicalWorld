#include "camera.h"

void Camera::updateView()
{
	m_view = glm::lookAt(m_center, m_lookAt, m_up);
}

void Camera::updateProjection()
{
	m_projection = glm::perspective(45.0f, m_size.x / static_cast<float>(m_size.y), 0.1f, 30.0f);
}

void Camera::translate(glm::vec3 translate)
{
	m_center += translate;
	m_lookAt += translate;
	updateView();
}

void Camera::setCenter(glm::vec3 center)
{
	m_center = center;
}

void Camera::setLookAt(glm::vec3 lookAt)
{
	m_lookAt = lookAt;
}

void Camera::setUp(glm::vec3 up)
{
	m_up = up;
}

glm::vec3 Camera::getCenter()
{
	return m_center;
}

glm::vec3 Camera::getLookAt()
{
	return m_lookAt;
}

glm::vec3 Camera::getUp()
{
	return m_up;
}

glm::mat4 Camera::getViewMat()
{
	return m_view;
}
glm::mat4 Camera::getProjMat()
{
	return m_projection;
}

glm::vec2 Camera::getNearFar()
{
	return glm::vec2(0.1,30);
}

glm::vec2 Camera::getSize()
{
	return m_size;
}
