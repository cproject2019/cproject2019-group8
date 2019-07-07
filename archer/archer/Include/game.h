#pragma once
#ifndef GAME_H
#define GAME_H

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "..\Include\resource_manager.h"
#include "..\Include\Archer.h"
#include "..\Include\camera.h"
#include "..\Include\game_map.h"


// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLboolean              Leftmouse = FALSE;
	GLuint                 Width, Height;
	GLfloat                xpos = 0.0f, ypos = 0.0f;
	Archer*                Archers;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	GLvoid Init();
	// GameLoop
	GLvoid processInput(glm::vec3* pPosition, float MovementSpeed, float dt);
	GLvoid Update(GLfloat dt);
	GLvoid Render();
	glm::mat4 mouse_rotatep();


private:
	GLvoid DoCollisions(GameShootingObject& );
	GLboolean PersonCollisions();
	GLboolean CheckArrowCollision(glm::vec3, GameObject);
	GLboolean CheckPersonCollision(glm::vec3, GameObject);
	GLboolean CheckPersonStarCollision(glm::vec3 Position, GameObject one);
	glm::vec3 SearchShootingTarget(glm::vec3 Position);
	GLvoid CheckArrowandWall();
};

#endif