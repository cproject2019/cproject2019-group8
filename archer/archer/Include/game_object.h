#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "..\Include\shader.h"


class GameObject
{
public:
	glm::vec3   Position, Size, Velocity, Direction ,Color;
	glm::mat4   Rotation;
	GLfloat     dt = 0.0f;
	GLfloat     Attack;
	GLboolean   Destroyed;
	GLboolean   Occupied = GL_FALSE;
	GLint FindingPathValue = 0;
	GameObject();
	GameObject(glm::vec3 pos, glm::vec3 size,  glm::vec3 color = glm::vec3(1.0f) );

};

#endif