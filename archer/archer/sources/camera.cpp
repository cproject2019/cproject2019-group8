#pragma once
#include "../Include/camera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) 
{
	Position = position;
}

Camera::~Camera()
{
	delete this;
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->Position, this->Position + this->Front, glm::vec3(0.0f, 1.0f, 0.0f));
}