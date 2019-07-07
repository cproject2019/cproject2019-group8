#include"..\Include\arrow.h"
float vertices[] =
{

	0.5f, 0.1f, 0.0f,    1.0f,0.0f, 0.0f,

	 0.5f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,

	 -0.5f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,

	0.5f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,

	-0.5f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,

	 -0.5f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,

	 0.5f,  0.2f, 0.0f,   1.0f,0.0f, 0.0f,

	 0.5f, -0.2f, 0.0f,   1.0f,0.0f, 0.0f,

	 0.9f,  0.0f, 0.0f,   1.0f,0.0f, 0.0f,
};
void Arrow::Init()
{
	GLuint VBO;
	glGenVertexArrays(1, &this->ArrowVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->ArrowVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Arrow::createarrow(glm::vec3 Position, glm::mat4 Rotation, GLfloat Attack)
{
	GLboolean useused = FALSE;
	for (GameObject& tile2 :this->arrow)
		if (tile2.Destroyed)
		{
			GameObject one;
			one.Direction = glm::vec3(Rotation[0][0], -Rotation[1][0], 0);
			one.Position = Position + 0.5f * one.Direction;
			one.Rotation = Rotation;
			one.Velocity = 10.0f * one.Direction;
			one.Attack = Attack;
			tile2 = one;
			useused = TRUE;
			break;
		}
	if (useused == FALSE)
	{
		GameObject one;
		one.Direction = glm::vec3(Rotation[0][0], -Rotation[1][0], 0);
		one.Position = Position + 0.5f * one.Direction;
		one.Rotation = Rotation;
		one.Velocity = 10.0f * one.Direction;
		one.Attack = Attack;
		this->arrow.push_back(one);
	}
}

void Arrow::DrawArrow() 
{
	ResourceManager::GetShader("person").Use();
	glBindVertexArray(this->ArrowVAO);
	for (GameObject& tile2 : this->arrow)
		if (!tile2.Destroyed)
		{
			glm::mat4 positionarrow = glm::translate(glm::mat4(1.0f), tile2.Position);
			glm::mat4 arrmodel = glm::scale(tile2.Rotation, glm::vec3(0.8f, 0.4f, 0.0f));
			arrmodel = positionarrow * arrmodel;
			ResourceManager::GetShader("person").SetMatrix4("model", arrmodel);
			glm::mat4 transcolor = glm::translate(glm::mat4(1.0f), glm::vec3(0.9f, 0.15f, 0.1f));
			ResourceManager::GetShader("person").SetMatrix4("colortrans", transcolor);
			glDrawArrays(GL_TRIANGLES, 0, 9);
		}
	glBindVertexArray(0);
}