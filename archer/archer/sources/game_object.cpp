#pragma once
#include "..\Include\game_object.h"


GameObject::GameObject()
	: Position(0.0f, 0.0f, 0.0f), Size(1.0f, 1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Destroyed(false) { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, glm::vec3 color )		
	: Position(pos), Size(size),  Color(color), Rotation(0.0f), Destroyed(false) { }

