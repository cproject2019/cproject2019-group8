#pragma once
#ifndef FINDINGPATH_H
#define FINDINGPATH_H

#include<vector>
#include "game_object.h"

class FindingPath 
{
public: 
	std::vector<GameObject> openlist;
	std::vector<GameObject> closedlist;
	std::vector<GameObject> path;
	GLint FindingPathValue;
	GLvoid Init(std::vector<GameObject>);
	std::vector<GameObject> FindingWay(GameObject goal, GameObject nowStay);
private:
	std::vector<GameObject> stays;
	GLboolean FindingNBH(GameObject now, GameObject goal);
	GLvoid PrintfPath(GameObject goal);
	GLboolean checkIfNear(GameObject one, GameObject two);
};
#endif