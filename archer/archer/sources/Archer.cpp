#include "..\Include\Archer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Archer::Archer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

Archer::~Archer()
{
	glDeleteVertexArrays(1, &this->VAO);
}
void Archer::CreateArcher(GLchar name) 
{
	GameShootingObject one;
	one.name = name;
	one.Startposition = glm::vec3(0.0f);
	this->Archers.push_back(one);
}

void Archer::ShootingIntervalUpdate(GLfloat dt, GLchar name)
{

}

void Archer::DrawArcher(glm::vec3 Position, glm::mat4 rotate)
{
	this->shader.Use();
	glBindVertexArray(this->VAO);
	glm::mat4 model_body = glm::mat4(1.0f);
	glm::mat4 model_hand_left = glm::mat4(1.0f);
	glm::mat4 model_hand_right = glm::mat4(1.0f);
	glm::mat4 model_leg_right = glm::mat4(1.0f);
	glm::mat4 model_leg_left = glm::mat4(1.0f);
	glm::mat4 model_head = glm::mat4(1.0f);
	glm::mat4 model_position = glm::mat4(1.0f);
	glm::mat4 model_body_tranform = glm::mat4(1.0f);
	glm::mat4 model_hand_left_tranform = glm::mat4(1.0f);
	glm::mat4 model_hand_right_tranform = glm::mat4(1.0f);
	glm::mat4 model_leg_right_tranform = glm::mat4(1.0f);
	glm::mat4 model_leg_left_tranform = glm::mat4(1.0f);
	glm::mat4 model_head_tranform = glm::mat4(1.0f);
	glm::mat4 model_stay_tranform = glm::mat4(1.0f);
	glm::mat4 model_position_tranform = glm::mat4(1.0f);
	glm::mat4 colortrans = glm::mat4(1.0f);

	model_position = glm::translate(glm::mat4(1.0f), Position);
	glm::mat4 transbody = glm::mat4(1.0f);
	transbody = glm::translate(transbody, glm::vec3(0.0f, 0.0f, -0.15f));
	transbody = glm::scale(transbody, glm::vec3(0.4f, 0.4f, 0.625f));
	model_body = model_position * rotate * transbody;

	glm::vec4 neck(0.0f, 0.0f, 0.0f, 1.0f);
	neck = model_position * neck;
	model_head_tranform = glm::mat4(1.0f);
	model_head_tranform = glm::rotate(model_head_tranform, (float)sin(glfwGetTime() * 2) / 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model_head_tranform = glm::scale(model_head_tranform, glm::vec3(0.25, 0.25f, 0.30f));
	model_head = glm::translate(glm::mat4(1.0f), glm::vec3(neck.x, neck.y, neck.z + 0.625f)) * rotate * model_head_tranform;
	this->shader.SetMatrix4("model", model_head);
	colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.3f, 0.2f));
	this->shader.SetMatrix4("colortrans", colortrans);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	this->shader.SetMatrix4("model", model_body); 
	colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.9f));
	this->shader.SetMatrix4("colortrans", colortrans);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::vec4 shd_left(0.0f, 0.0f, 0.0f, 1.0f);
	shd_left = model_position * shd_left;
	model_hand_left_tranform = glm::mat4(1.0f);
	model_hand_left_tranform = glm::translate(model_hand_left_tranform, glm::vec3(0.0f, -0.525f, 0.475f));
	model_hand_left_tranform = glm::rotate(model_hand_left_tranform, (float)sin(glfwGetTime() * 2 + 1.0f) / 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model_hand_left_tranform = glm::translate(model_hand_left_tranform, glm::vec3(0.0f, 0.0f, -0.20f));
	model_hand_left_tranform = glm::scale(model_hand_left_tranform, glm::vec3(0.15f, 0.15f, 0.20f));
	model_hand_left = glm::translate(glm::mat4(1.0f), glm::vec3(shd_left.x, shd_left.y, shd_left.z)) * rotate * model_hand_left_tranform;
	this->shader.SetMatrix4("model", model_hand_left);

	colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.7f, 0.2f));
	this->shader.SetMatrix4("colortrans", colortrans);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::vec4 shd_right(0.0f, 0.0f, 0.0f, 1.0f);
	shd_right = model_position * shd_right;
	model_hand_right_tranform = glm::mat4(1.0f);
	model_hand_right_tranform = glm::translate(model_hand_right_tranform, glm::vec3(0.0f, 0.525f, 0.475f));
	model_hand_right_tranform = glm::rotate(model_hand_right_tranform, (float)sin(glfwGetTime() * 2 - 1.0f) / 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model_hand_right_tranform = glm::translate(model_hand_right_tranform, glm::vec3(0.0f, 0.0f, -0.20f));
	model_hand_right_tranform = glm::scale(model_hand_right_tranform, glm::vec3(0.15f, 0.15f, 0.20f));
	model_hand_right = glm::translate(glm::mat4(1.0f), glm::vec3(shd_right.x, shd_right.y, shd_right.z)) * rotate * model_hand_right_tranform;
	this->shader.SetMatrix4("model", model_hand_right);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::vec4 pp_left(0.0f, 0.0f, 0.0f, 1.0f);
	pp_left = model_position * pp_left;
	model_leg_left_tranform = glm::mat4(1.0f);
	model_leg_left_tranform = glm::translate(model_leg_left_tranform, glm::vec3(-0.05f, -0.50f, -0.775f));
	model_leg_left_tranform = glm::rotate(model_leg_left_tranform, (float)sin(glfwGetTime() * 2 - 1.0f) / 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model_leg_left_tranform = glm::translate(model_leg_left_tranform, glm::vec3(0.0f, 0.0f, -0.15f));
	model_leg_left_tranform = glm::scale(model_leg_left_tranform, glm::vec3(0.175f, 0.175f, 0.15f));
	model_leg_left = glm::translate(glm::mat4(1.0f), glm::vec3(pp_left.x, pp_left.y, pp_left.z)) * rotate * model_leg_left_tranform;
	colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, 0.1f, 0.8f));
	this->shader.SetMatrix4("colortrans", colortrans);
	this->shader.SetMatrix4("model", model_leg_left);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glm::vec4 pp_right(0.0f, 0.0f, 0.0f, 1.0f);
	pp_right = model_position * pp_right;
	model_leg_right_tranform = glm::mat4(1.0f);
	model_leg_right_tranform = glm::translate(model_leg_right_tranform, glm::vec3(-0.05f, 0.50f, -0.775f));
	model_leg_right_tranform = glm::rotate(model_leg_right_tranform, (float)sin(glfwGetTime() * 2 + 1.0f) / 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model_leg_right_tranform = glm::translate(model_leg_right_tranform, glm::vec3(0.0f, 0.0f, -0.15f));
	model_leg_right_tranform = glm::scale(model_leg_right_tranform, glm::vec3(0.175f, 0.175f, 0.15f));
	model_leg_right = glm::translate(glm::mat4(1.0f), glm::vec3(pp_right.x, pp_right.y, pp_right.z)) * rotate * model_leg_right_tranform;
	this->shader.SetMatrix4("model", model_leg_right);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Archer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
	};
	static GLfloat colors[36 * 3];
	for (int v = 0; v < 36; v++)
	{
		colors[3 * v + 0] = 0.0f;
		colors[3 * v + 1] = 0.0f;
		colors[3 * v + 2] = 0.0f;
	}
	
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
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