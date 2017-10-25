#pragma once

#include "..\..\stdafx.h"
#include "..\object.h"

class Camera: public Object
{
private:
	glm::vec2 m_size;

	glm::vec3 m_center;
	glm::vec3 m_lookAt;
	glm::vec3 m_up;

	glm::mat4 m_view;
	glm::mat4 m_projection;


public:
	Camera(glm::vec2 size)
		: m_size(size)
	{}

	void setCenter(glm::vec3);
	void setLookAt(glm::vec3);
	void setUp(glm::vec3);

	glm::vec3 getCenter();
	glm::vec3 getLookAt();
	glm::vec3 getUp();

	glm::mat4 getViewMat();
	glm::mat4 getProjMat();

	glm::vec2 getNearFar();
	glm::vec2 getSize();

	//These methods has to be called after properties are changed
	void updateView();
	void updateProjection();

	void translate(glm::vec3);

};