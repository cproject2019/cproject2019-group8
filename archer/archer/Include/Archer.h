#ifndef ARCHER_H
#define ARCHER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "..\Include\game_shootingobject.h"
#include "shader.h"
class Archer
{
public:
	Shader shader;
	std::vector<GameShootingObject> Archers;
	GLfloat playerSpeed = 3.0f;
	Archer(Shader& shader);
	~Archer();
	GLuint VAO;
	void CreateArcher(GLchar name);
	void DrawArcher(glm::vec3 Position, glm::mat4 rotate);
	void ShootingIntervalUpdate(GLfloat dt, GLchar name);
private:
	void initRenderData();
};
#endif