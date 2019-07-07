#pragma once
#ifndef HPEXPSTRIP_H
#define HPEXPSTRIP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Include/resource_manager.h"

class HPEXPStrip
{
public:
	GLuint VAO;
	GLvoid Init();
	GLvoid DrawHPStrip(glm::vec3 Position, GLfloat currentHealth);
	GLvoid DrawEXPStrip(glm::vec3 Position, GLfloat currentEXP);
private:
};
#endif