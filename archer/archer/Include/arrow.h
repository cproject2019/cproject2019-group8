#pragma once

#ifndef GAMEARROW_H
#define GAMEARROW_H
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Include/game_object.h"
#include "../Include/resource_manager.h"

class
	Arrow
{
public:
	std::vector<GameObject> arrow;
	GLuint ArrowVAO;
	GLfloat existtime = 0.8f;
	Arrow() 
	{
	}
	void Init();
	void createarrow(glm::vec3 Position,glm::mat4 Rotation, GLfloat Attack);
	void DrawArrow();
private:
};
	
#endif