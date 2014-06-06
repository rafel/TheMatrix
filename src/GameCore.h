/*
 * GameCore.h
 *
 *  Created on: May 7, 2014
 *      Author: rafel
 */

#ifndef GAMECORE_H_
#define GAMECORE_H_

#include <glm/glm.hpp>
#include "Window.h"
#include "Camera.h"
#include "Environment.h"

extern bool lightOnGame;
void GLFWCALL onMouseButton( int button, int action );


class GameCore
{
public:
	GameCore();
	~GameCore();
	void start();

	glm::mat4 view;
private:
	/* these two are used to generate a delata value that is used overall in the game */
	void calculateDelta();
	float lastFrameTime;
	float delta;
	/*************************/

	void startGameLoop();
	void checkKeyPress();
	int gameState;
	bool running;
	Window* windowOpengl;
	Environment* environment;
	glm::vec3 cameraPosition;
	Camera* camera;
};

#endif /* GAMECORE_H_ */
