#pragma once
#include "..\Include\game_shootingobject.h"


GameShootingObject::GameShootingObject()
	: Position(0.0f, 0.0f, 0.0f), Size(1.0f, 1.0f, 1.0f), Color(1.0f) { }

GameShootingObject::GameShootingObject(glm::vec3 pos, glm::vec3 size, glm::vec3 color)
	: Position(pos), Size(size), Color(color) { }

