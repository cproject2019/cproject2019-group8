#include "..\Include\HPEXPStrip.h"

GLvoid HPEXPStrip::Init()
{
	GLuint VBO;
	GLfloat Vertex[]
	{
		-1.0f, -0.2f, 0.0f,
		1.0f, -0.2, 0.0f,
		-1.0f, 0.2f, 0.0f,
		-1.0f, 0.2f, 0.0f,
		1.0f, 0.2f, 0.0f,
		1.0f,-0.2f, 0.0f
	};
	static GLfloat colors[6 * 3];
	for (int v = 0; v < 6; v++)
	{
		colors[3 * v + 0] = 0.0f;
		colors[3 * v + 1] = 0.0f;
		colors[3 * v + 2] = 0.0f;
	}

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLvoid HPEXPStrip::DrawHPStrip(glm::vec3 Position,GLfloat currentHealth)
{
	ResourceManager::GetShader("person").Use();
	glBindVertexArray(this->VAO);
	glm::mat4 Translate = glm::translate(glm::mat4(1.0), Position);
	Translate = glm::translate(Translate,glm::vec3(0.0f,0.4f,2.0f));
	glm::mat4 model = glm::scale(Translate, glm::vec3(currentHealth * 0.1f, 0.5f, 1.0f));
	ResourceManager::GetShader("person").SetMatrix4("model", model);
	glm::mat4 transcolor = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f,0.0f,0.0f));
	ResourceManager::GetShader("person").SetMatrix4("colortrans", transcolor);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	
}
GLvoid HPEXPStrip::DrawEXPStrip(glm::vec3 Position, GLfloat currentEXP)
{
	ResourceManager::GetShader("person").Use();
	glBindVertexArray(this->VAO);
	glm::mat4 Translate = glm::translate(glm::mat4(1.0), Position);
	Translate = glm::translate(Translate, glm::vec3(0.0f, 0.6f, 2.0f));
	glm::mat4 model = glm::scale(Translate, glm::vec3(currentEXP *0.0167f, 0.5f, 1.0f));
	ResourceManager::GetShader("person").SetMatrix4("model", model);
	glm::mat4 transcolor = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ResourceManager::GetShader("person").SetMatrix4("colortrans", transcolor);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}