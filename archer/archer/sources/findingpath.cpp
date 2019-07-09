#include"..\Include\findingpath.h"

GLvoid FindingPath::Init(std::vector<GameObject> stays) 
{
	this->stays = stays;
}
std::vector<GameObject> FindingPath::FindingWay(GameObject goal, GameObject nowStay)
{

	this->FindingPathValue = 0;
	this->closedlist.clear();
	this->openlist.clear();
	this->closedlist.push_back(nowStay);
	for (GameObject& one : this->stays)
	{
		one.FindingPathValue = 0;
		if (one.Position != nowStay.Position)
		{
			this->openlist.push_back(one);
		}
	}
	this->FindingPathValue++;
	int i = 0;
	for (GLboolean found = GL_FALSE; found == GL_FALSE; this->FindingPathValue++)
	{
		std::vector<GameObject>temporaryCheckList;
		temporaryCheckList.clear();
		for (GameObject& one : this->closedlist)
		{
			if (one.FindingPathValue == this->FindingPathValue - 1)
			{
				temporaryCheckList.push_back(one);
			}
		}
		for (GameObject& one : temporaryCheckList)
		{
			if (FindingPath::FindingNBH(one, goal) == GL_TRUE)
			{
				found = GL_TRUE;
				break;
			}
		}
	}
	PrintfPath(goal);

	return this->path;
}
GLboolean FindingPath::FindingNBH(GameObject now, GameObject goal)
{
	GLint vecposition = 0;
	GLint foundnum = 0;
	GLint deletetime = 0;
	GLint deteleposition[4] ;
	for (GameObject& one : this->openlist)
	{
		if (this->checkIfNear(one, now))
		{
			one.FindingPathValue = this->FindingPathValue;
			GameObject temporary = one;
			this->closedlist.push_back(temporary);
			if ((abs(one.Position.x-goal.Position.x)+abs(one.Position.y-goal.Position.y))<=0.1f)
			{
				return GL_TRUE;
			}
			
			deteleposition[deletetime] = vecposition - foundnum;
			deletetime++;
			foundnum++;
		}
		vecposition++;
	}
	for (deletetime = 0; deletetime <= foundnum-1; deletetime++)
	{
		openlist.erase(openlist.begin() + deteleposition[deletetime]);
	}
	return GL_FALSE;
}

GLvoid FindingPath::PrintfPath(GameObject goal)
{
	this->path.clear();
	std::vector<GameObject> reversedPath;
	for (this->FindingPathValue--; this->FindingPathValue >= 0; this->FindingPathValue--)
	{
		for (GameObject& one : closedlist)
		{
			if (reversedPath.size() == 0)
			{
					reversedPath.push_back(goal);
					break;
			}
			else
			{
				if (one.FindingPathValue == this->FindingPathValue && this->checkIfNear(reversedPath[reversedPath.size() - 1], one))
				{
					reversedPath.push_back(one);
					break;
				}
			}
		}
	}
	for (GLint count=0;count<reversedPath.size();count++)
	{
		this->path.push_back(reversedPath[reversedPath.size()-count-1]);
	}
}

GLboolean FindingPath::checkIfNear(GameObject one, GameObject two)
{

	if ((abs(one.Position.x - two.Position.x)+ abs(one.Position.y - two.Position.y))<=1.1f)
	{
		return GL_TRUE;
	}
	else
	{
		return GL_FALSE;
	}
}