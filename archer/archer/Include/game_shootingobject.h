#pragma once

#ifndef GAMESHOOTINGOBJECT_H
#define GAMESHOOTINGOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<vector>
#include "..\Include\shader.h"
#include "..\Include\game_object.h"
#include"..\Include\findingpath.h"
#include "../Include/resource_manager.h"
class GameShootingObject
{
public:
	glm::vec3   Position, Size, Velocity, Direction = glm::vec3(1.0f), Color,Startposition;
	glm::mat4   Rotation = glm::mat4(1.0f);
	GameObject Goal;//star
	FindingPath findingPath;
	std::vector<GameObject>  Path;
	GLboolean abletoshoot = GL_TRUE;
	GLboolean walking = GL_FALSE;
	GLboolean PathFinding = GL_FALSE;
	GLboolean skillGatling = FALSE;
	GLfloat shootinterval = 0.7f;
	GLfloat shootduringtime = 0.0f;
	GLfloat Attack = 1.0f;
	GLfloat speed = 3.0f;
	GLfloat Health = 5.0f;
	GLfloat CurrentHealth = 5.0f;
	GLfloat CurrentEXP = 0.0f;
	GLint Level = 1;
	GLchar  name;
	GLuint step = 1;

	GameShootingObject();
	GameShootingObject(glm::vec3 pos, glm::vec3 size, glm::vec3 color = glm::vec3(1.0f));
};

#endif