#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <glm/glm.hpp>
#include "graphicssettings.h"
#include <list>
#include <algorithm>    // std::for_each
#include "Hall.h"
#define MAX_HALLS	16

class Environment
{
public:
	Environment(glm::mat4 projMatrix);
	~Environment();
	void draw(glm::mat4 cameraPosition, float delta);
	void update(glm::vec3 cameraPosition);
	std::vector<int> findNeededHallsInTheRightPosition( int currentHall);
	std::vector<int> findAllFreeHalls( std::vector<int> neededHalls);
	void setProjMatrix(glm::mat4);
	void reset();
	void show();
	void mergeHalls(int theHall,int leftEdge,int rightEdge, int backEdge);
	Hall* theHalls[MAX_HALLS];
	glm::vec3 checkCollision(glm::vec3 cameraPosition);
	int currentHall;
private:
	void drawStartScreen();

	glm::mat4 projMatrix;
	glm::mat4 cameraPosition;
	float delta;
	Hall* hall;
	Hall* hall2;
	Hall* hall3;
	Hall* hall4;
	Hall* hall5;
	Hall* hall6;
	Hall* hall7;
};


#endif
