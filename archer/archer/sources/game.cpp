#include "..\Include\game.h"
#include"..\Include\arrow.h"
#include"..\Include\findingpath.h"
#include "..\Include\HPEXPStrip.h"

#include <vector>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
GameMap* archerMap;
Arrow gamearrow;
HPEXPStrip hpexpstrip;
glm::mat4 rotatep = glm::mat4(1.0f);
glm::vec3 pPosition;
GLboolean mouserealised = TRUE;
GLchar Player = 0;
GLchar NPC1 = 1;
GLchar NPC2 = 2;
GLchar NPC3 = 3;

GLvoid UpdatePosition(GameShootingObject& one);
GameObject SearchStar(glm::vec3 nowposition);
GameObject& GetArcherNowStay(glm::vec3 Position);

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	camera.~camera();
	delete this->Archers;
	delete archerMap;
}

GLvoid Game::Init()
{
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	gamearrow.Init();
	ResourceManager::LoadShader("resources\\shaders\\shader.vs", "resources\\shaders\\shader.fs", nullptr, "person");
	ResourceManager::GetShader("person").Use();
	ResourceManager::GetShader("person").SetMatrix4("projection", projection);
	ResourceManager::GetShader("person").SetMatrix4("view", view);
	this->Archers = new Archer(ResourceManager::GetShader("person"));
	this->Archers->CreateArcher(Player);
	hpexpstrip.Init();
	ResourceManager::LoadShader("resources\\shaders\\shader1.vs", "resources\\shaders\\shader1.fs", nullptr, "Map");
	ResourceManager::GetShader("Map").Use();
	ResourceManager::GetShader("Map").SetMatrix4("projection", projection);
	ResourceManager::GetShader("Map").SetMatrix4("view", view);
	archerMap = new GameMap(ResourceManager::GetShader("Map"));
	archerMap->Load("resources\\vectex.txt");

	GameShootingObject NPCone;
	NPCone.name = NPC1;
	NPCone.Position = glm::vec3(-10.5f, -12.5f, 0.0f);
	NPCone.Rotation = glm::mat4(1.0f);
	NPCone.Startposition = glm::vec3(-10.5f, -12.5f, 0.0f);
	NPCone.findingPath.Init(archerMap->Stays);
	this->Archers->Archers.push_back(NPCone);

	GameShootingObject NPCtwo;
	NPCtwo.name = NPC2;
	NPCtwo.Position = glm::vec3(9.5f, 12.5f, 0.0f);
	NPCtwo.Startposition = glm::vec3(9.5f, 12.5f, 0.0f);
	NPCtwo.Rotation = glm::mat4(1.0f);
	NPCtwo.findingPath.Init(archerMap->Stays);
	this->Archers->Archers.push_back(NPCtwo);

	GameShootingObject NPCthree;
	NPCthree.name = NPC3;
	NPCthree.Position = glm::vec3(18.5f, 15.5f, 0.0f);
	NPCthree.Rotation = glm::mat4(1.0f);
	NPCthree.findingPath.Init(archerMap->Stays);
	this->Archers->Archers.push_back(NPCthree);

}

GLvoid Game::Update(GLfloat dt)
{
	archerMap->UpdateStars();
	rotatep = mouse_rotatep();
	glm::mat4 view = camera.GetViewMatrix();
	ResourceManager::GetShader("person").SetMatrix4("view", view);
	archerMap->mapshader.Use();
	archerMap->mapshader.SetMatrix4("view", view);
	this->processInput( &pPosition, this->Archers->playerSpeed, dt);
	for (GameShootingObject& one : this->Archers->Archers)
	{
		for (GameObject& tile2 : archerMap->BlueStars)//check stars collision
		{
			if (!tile2.Destroyed)
			{
				if (CheckPersonStarCollision(one.Position, tile2))
				{
					for (GameObject& checkStays : archerMap->Stays)
					{
						if (checkStays.Position == tile2.Position)
						{
							checkStays.Occupied = FALSE;
						}
					}
					tile2.Destroyed = TRUE;
					archerMap->BlueStarNum -= 1;
					one.CurrentEXP += 1.0f;
				}

			}
		}
		for (GameObject& tile2 : archerMap->RedStars)
		{
			if (!tile2.Destroyed)
			{
				if (CheckPersonStarCollision(one.Position, tile2))
				{
					for (GameObject& checkStays : archerMap->Stays)
					{
						if (checkStays.Position == tile2.Position)
						{
							checkStays.Occupied = FALSE;
						}
					}
					tile2.Destroyed = GL_TRUE;
					archerMap->RedStarNum -= 1;
					one.CurrentHealth += 1.0f;
					if (one.CurrentHealth >= one.Health)
					{
						one.CurrentHealth = one.Health;
					}
				}
			}
		}
		if (one.name == Player) 
		{
			if (!this->Leftmouse || one.skillGatling)
				mouserealised = TRUE;
			if (this->Leftmouse == TRUE && one.abletoshoot == TRUE && mouserealised == TRUE)
			{
				gamearrow.createarrow(pPosition, rotatep,one.Attack);
				one.abletoshoot = FALSE;
				mouserealised = FALSE;
			}
			else
				one.shootduringtime += dt;
			
			if (one.shootduringtime >= one.shootinterval)
			{
				one.shootduringtime = 0;
				one.abletoshoot = TRUE;
			}
			one.Position = pPosition;
			one.Rotation = rotatep;
		}
		else
		{
			if(one.abletoshoot == GL_FALSE)
			{
				one.shootduringtime += dt;
				if (one.shootduringtime >= one.shootinterval)
				{
					one.shootduringtime = 0.0f;
					one.abletoshoot = GL_TRUE;
				}
			}
			if (one.abletoshoot == GL_TRUE)
			{
				glm::vec3 oneTarget = this->SearchShootingTarget(one.Position);
				if (oneTarget != glm::vec3(0.0f))
				{
					glm::vec3 oneDirection = glm::normalize(oneTarget - one.Position);
					one.Rotation[0][0] = oneDirection.x;
					one.Rotation[0][1] = oneDirection.y;
					one.Rotation[1][0] = -oneDirection.y;
					one.Rotation[1][1] = oneDirection.x;
					gamearrow.createarrow(one.Position, one.Rotation, one.Attack);
					one.abletoshoot = GL_FALSE;
				}
			}
			if (one.walking == GL_FALSE)
			{
				if (one.PathFinding == GL_FALSE) 
				{
					one.PathFinding = GL_TRUE;
					std::thread findpath(UpdatePosition ,std::ref(one));
					findpath.detach();
				}
			}
			else
			{
				glm::vec3 displacement = glm::vec3(one.Path[one.step].Position.x, one.Path[one.step].Position.y, 0.0) - one.Position - one.Velocity * dt;
				if (displacement == glm::vec3(0.0f)) //if directly meet the stepping point
				{
					one.step++;
					if (one.step >= (one.Path.size()))//prevent from subscript issue and just stop running 
					{
						one.walking = GL_FALSE;
						one.step = 1;
					}
					else
					{
						one.Direction = glm::normalize(glm::vec3(one.Path[one.step].Position.x, one.Path[one.step].Position.y, 0.0f) - one.Position);
						one.Velocity = one.speed * one.Direction;
						one.Position = one.Velocity * dt + glm::vec3(one.Path[one.step].Position.x, one.Path[one.step].Position.y, 0.0f);
					}
				}
				else
				{
					glm::vec3 checkvec = glm::normalize(displacement) + one.Direction;
					if (glm::dot(checkvec, checkvec) <= 0.1f)//if the direction is going to be reversed;
					{
						one.step++;
						if (one.step >= (one.Path.size()))
						{
							one.walking = GL_FALSE;
							one.step = 1;
						}
						else
						{
							one.Direction = glm::normalize(one.Path[one.step].Position - one.Path[one.step-1].Position);
							one.Velocity = one.speed * one.Direction;
							one.Position = one.Direction * sqrt(glm::dot(displacement, displacement)) + glm::vec3(one.Path[one.step-1].Position.x, one.Path[one.step-1].Position.y, 0.0f);
						}
					}
					else
					{
						one.Position = one.Position + one.Velocity * dt;
					}
				}
				
			}

		}
		this->DoCollisions(one);
		if (one.CurrentEXP >= 30.f)
		{
			GLint randomnum;
			one.CurrentEXP -= 30.0f;
			one.Level += 1;
			if (one.skillGatling == GL_FALSE)
			{
				randomnum = (int)rand() % 5;
			}
			else
			{
				randomnum = (int)rand() % 4;
			}

			if (randomnum == 0)
			{
				one.Attack += 0.2f;
			}
			if (randomnum == 1)
			{
				one.shootinterval -= 0.08f;
			}
			if (randomnum == 2)
			{
				one.speed += 0.04f;
			}
			if (randomnum == 3)
			{
				one.Health += 0.5f;
			}
			if (randomnum == 4)
			{
				one.skillGatling = GL_TRUE;
			}
		}
		if (one.CurrentHealth<=0.0f)
		{
			one.CurrentHealth = one.Health;
			one.Attack = 1.0f;
			one.Health = 5.0f;
			one.shootinterval = 0.7f;
			one.speed = 3.0f;
			one.skillGatling = GL_FALSE;
			one.CurrentEXP = 0.0f;
			if (one.name == Player)
			{
				one.Position = one.Startposition;
				pPosition = one.Startposition;

			}
			else 
			{
				if(one.walking == GL_TRUE)
				{
					one.walking = GL_FALSE;
					one.step = 1;
					one.Position = one.Startposition;
				}
			}
			for (GLint looptimes = 0;looptimes<one.Level;looptimes++) 
			{
				GLint randomnum;
				if (one.skillGatling == GL_FALSE)
				{
					randomnum = (int)rand() % 5;
				}
				else
				{
					randomnum = (int)rand() % 4;
				}

				if (randomnum == 0)
				{
					one.Attack += 0.2f;
				}
				if (randomnum == 1)
				{
					one.shootinterval -= 0.08f;
				}
				if (randomnum == 2)
				{
					one.speed += 0.04f;
				}
				if (randomnum == 3)
				{
					one.Health += 0.5f;
				}
				if (randomnum == 4)
				{
					one.skillGatling = GL_TRUE;
				}
			}
		}
		
	}
	this->CheckArrowandWall();
	for (GameObject& tile2 : gamearrow.arrow)
		if (!tile2.Destroyed)
		{
			tile2.dt += dt;
			tile2.Position += dt * (tile2.Velocity);
			if (tile2.dt >= 0.6f)
				tile2.Destroyed = TRUE;
		}
}

GLvoid Game::Render()
{
	archerMap->draw();
	gamearrow.DrawArrow();
	for (GameShootingObject& one : this->Archers->Archers)
	{
		if (one.name == Player) 
		{
			one.Position = pPosition;
		}
		this->Archers->DrawArcher(one.Position, one.Rotation);
		hpexpstrip.DrawHPStrip(one.Position, one.CurrentHealth);
		hpexpstrip.DrawEXPStrip(one.Position, one.CurrentEXP);
	}
}

GLvoid Game::processInput(glm::vec3* pPosition, float MovementSpeed, float deltaTime)
{
	if (this->Keys[GLFW_KEY_ESCAPE])
		this->State = GAME_MENU;

	if (this->State == GAME_ACTIVE)
	{
		float velocity = MovementSpeed * deltaTime;
		glm::vec3 changepPosition = glm::vec3(0.0f);
		if (this->Keys[GLFW_KEY_W])
		{
			changepPosition += glm::vec3(0.0f, 1.0f, 0.0f);
		}
		if (this->Keys[GLFW_KEY_S])
		{
			changepPosition -= glm::vec3(0.0f, 1.0f, 0.0f);
		}
		if (this->Keys[GLFW_KEY_A])
		{
			changepPosition -= glm::vec3(1.0f, 0.0f, 0.0f);
		}
		if (this->Keys[GLFW_KEY_D])
		{
			changepPosition += glm::vec3(1.0f, 0.0f, 0.0f);
		}
		if (changepPosition != glm::vec3(0.0f))
		{
			changepPosition = glm::normalize(changepPosition) * velocity;
		}
		(*pPosition) += changepPosition;
		if (this->PersonCollisions())
		{
			(*pPosition) -= changepPosition;
		}
		else
		{
			camera.Position.x = (*pPosition).x;
			camera.Position.y = (*pPosition).y;
		}
	}
}
glm::mat4 Game::mouse_rotatep()
{
	glm::mat4 rotatep = glm::mat4(1.0f);
	this->xpos -= (GLfloat)this->Width * 0.5;
	this->ypos -= (GLfloat)this->Height * 0.5;
	if (xpos != 0 && ypos != 0)
	{
		glm::vec3 rotateD = glm::normalize(glm::vec3(this->xpos, this->ypos, 0.0f));
		rotatep[0][0] = rotateD.x;
		rotatep[0][1] = -rotateD.y;
		rotatep[1][0] = rotateD.y;
		rotatep[1][1] = rotateD.x;
	}
	return rotatep;
}

GLvoid Game::DoCollisions(GameShootingObject& one)
{
	for (GameObject& arrow : gamearrow.arrow)
	{
		if (!arrow.Destroyed)
		{
			if (Game::CheckArrowCollision(one.Position, arrow))
			{
					arrow.Destroyed = GL_TRUE;
					one.CurrentHealth -= arrow.Attack;
			}
		}
	}
	
} 
GLboolean Game::CheckArrowCollision(glm::vec3 Position, GameObject arrow)
{

	if ((arrow.Position.x + 0.9f * arrow.Direction.x) >= ((Position.x) - 0.5f) &&
		(arrow.Position.x + 0.9f * arrow.Direction.x) <= ((Position.x) + 0.5f) &&
		(arrow.Position.y + 0.9f * arrow.Direction.y) <= ((Position.y) + 0.5f) &&
		(arrow.Position.y + 0.9f * arrow.Direction.y) >= ((Position.y) - 0.5f))
		return TRUE;
	else return FALSE;

}
GLboolean Game::PersonCollisions()
{
	GLboolean collision = GL_FALSE;
	for (GameObject& wall : archerMap->Walls)
	{
		if (Game::CheckPersonCollision(pPosition, wall))
		{
			collision = GL_TRUE;
			break;
		}
	}
	return collision;
}
GLboolean Game::CheckPersonCollision(glm::vec3 Position, GameObject one)
{
	GLboolean collisionX = (Position.x - one.Position.x) <= 1.0f && (Position.x - one.Position.x) >= -1.0f;
	GLboolean collisionY = (Position.y - one.Position.y) <= 1.0f && (Position.y - one.Position.y) >= -1.0f;
	return collisionX && collisionY;
}
GLboolean Game::CheckPersonStarCollision(glm::vec3 Position, GameObject one)
{
	GLboolean collisionX = (Position.x - one.Position.x) <= 0.8f && (Position.x - one.Position.x) >= -0.8f;
	GLboolean collisionY = (Position.y - one.Position.y) <= 0.8f && (Position.y - one.Position.y) >= -0.8f;
	return collisionX && collisionY;
}
GLvoid Game::CheckArrowandWall()
{
	for (GameObject& arrow : gamearrow.arrow)
	{
		for (GameObject& wall : archerMap->Walls)
		{
			if (!arrow.Destroyed)
			{
				if (Game::CheckArrowCollision(wall.Position, arrow))
				{
					arrow.Destroyed = GL_TRUE;
				}
			}
		}
	}
}

GameObject SearchStar(glm::vec3 nowposition) 
{
	GameObject NearestStar;
	for (GameObject one : archerMap->BlueStars)
	{
		if (one.Destroyed == GL_FALSE)
		{
			NearestStar = one;
			break;
		}
	}
	for (GameObject one : archerMap->BlueStars)
	{
		if((abs(one.Position.x- nowposition.x) + abs(one.Position.y -nowposition.y))
			<= (abs(NearestStar.Position.x - nowposition.x) + abs(NearestStar.Position.y - nowposition.y)) 
			&& one.Destroyed==GL_FALSE)
		{ 
			NearestStar = one;
		}	
	}
	return NearestStar;
}
GameObject& GetArcherNowStay(glm::vec3 Position)
{
	for (GameObject& one : archerMap->Stays)
	{
		if (abs(one.Position.x - Position.x) <= 0.5f && abs(one.Position.y - Position.y) <= 0.5f)
		{
			return one;
		}
	}
}
GLvoid UpdatePosition(GameShootingObject& one)
{

	one.Goal = SearchStar(one.Position);
	one.Path.clear();
	one.Path = one.findingPath.FindingWay(one.Goal, GetArcherNowStay(one.Position));
	if(one.step>=0)
	{ 
		one.Direction = glm::normalize(glm::vec3(one.Path[one.step].Position.x, one.Path[one.step].Position.y, 0.0) - one.Position); 
	}
	one.Velocity = one.speed * one.Direction; //set the velocity
	one.walking = GL_TRUE;
	one.step = 1; //start from the second step. the first step is where now it stands 	
	one.PathFinding = GL_FALSE;
}
glm::vec3 Game::SearchShootingTarget(glm::vec3 Position)
{
	glm::vec3 NearesrArcherPosition = glm::vec3(0.0f);
	for (GameShootingObject& one : this->Archers->Archers)
	{
		if ( one.Position!=Position)
		{
			NearesrArcherPosition = one.Position;
			break;
		}
	}
	for (GameShootingObject& one : this->Archers->Archers)
	{
		if ((abs(one.Position.x - Position.x) + abs(one.Position.y - Position.y))
			<= (abs(NearesrArcherPosition.x - Position.x) + abs(NearesrArcherPosition.y - Position.y))
			&& one.Position != Position)
		{
			NearesrArcherPosition = one.Position;
		}
	}
	return NearesrArcherPosition;
}
