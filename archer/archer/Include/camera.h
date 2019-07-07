#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera(glm::vec3 position);
	~Camera();
	glm::mat4 GetViewMatrix();
};
#endif