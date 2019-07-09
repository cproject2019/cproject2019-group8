#include "..\Include\game_map.h"

#include <fstream>
#include <sstream>

GLint seedtimes = rand();
GLint stays = 0;
GLint redneednum = 60;
GLint blueneednum = 400;
GLuint VAO2;
GameMap::GameMap(Shader& shader) 
{
	this->mapshader = shader;
}
void GameMap::Load(const GLchar* file)
{
	GLuint VBO;
	float vertices[] = {
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f
	};
	GLuint  VBO2;
	GLfloat vertices2[] = {
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
	glGenVertexArrays(1, &this->MapVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->MapVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint colorVBO;
	glGenBuffers(1, &colorVBO);
	glBindVertexArray(colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	ResourceManager::LoadTexture("resources\\textures\\container.jpg", GL_TRUE, "wall");
	ResourceManager::LoadTexture("resources\\textures\\block_solid.jpg", GL_TRUE, "stay");
	this->Walls.clear();
	GLuint tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData);
	}
}

void GameMap::init(std::vector<std::vector<GLuint>> tileData)
{
	// Calculate dimensions
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < 49; y++)
	{
		for (GLuint x = 0; x < 45; x++)
		{
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 1) // Solid
			{
				glm::vec3 pos(1.0f * x-24.5f, 1.0f * y-22.5f, 0.0f);
				glm::vec3 size(0.5f, 0.5, 1.0);
				GameObject obj(pos, size,glm::vec3(0.8f, 0.8f, 0.7f));
				this->Walls.push_back(obj);
			}
			if (tileData[y][x] == 0) // Solid
			{
				glm::vec3 pos(1.0f * x - 24.5f, 1.0f * y - 22.5f, -1.0f);
				glm::vec3 size(0.5f, 0.5f, 0.0f);
				GameObject obj(pos, size, glm::vec3(0.8f, 0.8f, 0.7f));
				this->Stays.push_back(obj);
				stays++;
			}
		}
	}
	this->FillBlueStars();
	this->FillRedStars();
}
void GameMap::UpdateStars() 
{
	this->FillBlueStars();
	this->FillRedStars();
}
void GameMap::draw()
{
	this->mapshader.Use();
	ResourceManager::GetTexture("wall").Bind();
	glm::mat4 translate = glm::mat4(1.0f);
	glBindVertexArray(this->MapVAO);
	for (GameObject& tile : this->Walls)
		if (!tile.Destroyed)
		{
			translate = glm::translate(glm::mat4(1.0f), tile.Position);
			translate = glm::scale(translate, tile.Size);
			this->mapshader.SetMatrix4("model", translate);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	ResourceManager::GetTexture("stay").Bind();
	for (GameObject& tile : this->Stays)
		if (!tile.Destroyed)
		{
			translate = glm::translate(glm::mat4(1.0f), tile.Position);
			translate = glm::scale(translate, tile.Size);
			this->mapshader.SetMatrix4("model", translate);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	ResourceManager::GetShader("person").Use();
	glBindVertexArray(0);
	glBindVertexArray(VAO2);
	glm::mat4 colortrans;
	for (GameObject& tile : this->RedStars)
		if (!tile.Destroyed)
		{
			translate = glm::translate(glm::mat4(1.0f), tile.Position);
			translate = glm::scale(translate, tile.Size);
			colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			ResourceManager::GetShader("person").SetMatrix4("model", translate);
			ResourceManager::GetShader("person").SetMatrix4("colortrans", colortrans);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	glm::mat4 transcolor = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f, 0.0f, 0.7f));
	ResourceManager::GetShader("person").SetMatrix4("colortrans", transcolor);
	for (GameObject& tile : this->BlueStars)
		if (!tile.Destroyed)
		{
			translate = glm::translate(glm::mat4(1.0f), tile.Position);
			translate = glm::scale(translate, tile.Size);
			colortrans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.8f));
			ResourceManager::GetShader("person").SetMatrix4("model", translate);
			ResourceManager::GetShader("person").SetMatrix4("colortrans", colortrans);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	glBindVertexArray(0);

}

void      GameMap::FillRedStars() 
{
	GLint randomnum = 0;
	for (; this->RedStarNum < redneednum; (this->RedStarNum)++)
	{
		srand(seedtimes * seedtimes);
		seedtimes++;
		for (GLboolean end = FALSE; end == FALSE;)
		{
			randomnum = (GLint)(rand() % stays);
			int staynum = 0;
			for (GameObject& tile : this->Stays)
			{
				if (staynum == randomnum)
				{
					if (tile.Occupied == TRUE)
					{
						break;
					}
					else
					{
						GLboolean FoundUsed = FALSE;
						for (GameObject& checkUsedStar : this->RedStars) 
						{
							if (checkUsedStar.Position==tile.Position)
							{
								checkUsedStar.Destroyed = FALSE;
								FoundUsed = TRUE;
								end = TRUE;
								break;
							}
						}
						if (FoundUsed == FALSE) 
						{
							GameObject one;
							one.Position = tile.Position;
							one.Size = glm::vec3(0.05f, 0.05f, 0.05f);
							this->RedStars.push_back(one);
							tile.Occupied = TRUE;
							end = TRUE;
						}
					}
				}
				staynum++;
			}
		}
	}
}
void      GameMap::FillBlueStars() 
{
	GLint randomnum = 0;
	for (; this->BlueStarNum < blueneednum; (this->BlueStarNum)++)
	{
		srand(seedtimes * seedtimes);
		seedtimes++;
		for (GLboolean end = GL_FALSE; end == GL_FALSE;)
		{
			randomnum = (GLint)(rand() % stays);
			int staynum = 0;
			for (GameObject& tile : this->Stays)
			{
				if (staynum == randomnum)
				{
					if (tile.Occupied == TRUE)
					{
						break;
					}
					else
					{
						GLboolean FoundUsed = FALSE;
						for (GameObject& checkUsedStar : this->BlueStars)
						{
							if (checkUsedStar.Position == tile.Position)
							{
								checkUsedStar.Destroyed = FALSE;
								FoundUsed = TRUE;
								end = TRUE;
								break;
							}
						}
						if (FoundUsed == FALSE)
						{
							GameObject one;
							one.Position = tile.Position;
							one.Size = glm::vec3(0.05f, 0.05f, 0.05f);
							this->BlueStars.push_back(one);
							tile.Occupied = TRUE;
							end = TRUE;
						}
					}
				}
				staynum++;
			}
		}
	}
}