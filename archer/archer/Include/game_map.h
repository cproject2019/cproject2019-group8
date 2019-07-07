#pragma once
#ifndef GAMEWALL_H
#define GAMEWALL_H
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Include/game_object.h"
#include "../Include/resource_manager.h"


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
class GameMap
{
public:
	// Level state
	std::vector<GameObject> Walls;
	std::vector<GameObject> Stays;
	std::vector<GameObject> RedStars;
	GLint RedStarNum = 0;
	std::vector<GameObject> BlueStars;
	GLint BlueStarNum = 0;
	GLuint MapVAO;
	Shader mapshader;
	// Constructor
	GameMap(Shader& shader);
	void      UpdateStars();
	void      Load(const GLchar* file);
	void      draw();
	void      FillRedStars();
	void      FillBlueStars();
private:
	void      init(std::vector<std::vector<GLuint>> tileData);
};

#endif