#include "GameCore.h"
#include "Window.h"
#include "Camera.h"
#include <iostream>
#include "graphicssettings.h"
int mouseX, mouseY;
const float rotationSpeed = 0.3f;

// Const. new Window, reset camera position
GameCore::GameCore()
{
	this->windowOpengl = new Window();
	windowOpengl->show();

	this->cameraPosition=glm::vec3(0,0,0);

	// Camera matrix
	this->view = glm::lookAt(
					glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
					glm::vec3(0,0,0), // and looks at the origin
					glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	   );

	this->camera = new Camera(60.0f, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 900000.0f, cameraPosition);
	//int mouseX, mouseY;
	glfwGetMousePos(&mouseX, &mouseY);
	this->camera->updateRotation(0,0);
}
const float translateSpeed = 0.08f;

// Deconst. remove all created objects
GameCore::~GameCore()
{
	delete windowOpengl;
	delete environment;
}

// Calculated delta time
void GameCore::calculateDelta()
{
	float time = glfwGetTime();
	float delta = time - lastFrameTime;
	lastFrameTime = time;
	this->delta = (delta)*1000/16.67f;
}

// Starts the game
void GameCore::start()
{
	try
	{
		this->running = true;



		this->environment = new Environment(camera->getProjMatrix());
		this->environment->show();


		// Starts gameloop
		startGameLoop();
	}
	catch(const char* s)
	{
		throw s;
	}
}

// GameLoop
void GameCore::startGameLoop()
{
	try
	{
		while(running)
		{
			calculateDelta();
			checkKeyPress();

			// Show environment
			environment->update(camera->getPosition());
			environment->draw(camera->getViewMatrix(),delta);

			// Camera position
			glm::vec3 pos = glm::vec3(camera->getPosition().x, 0.0f, camera->getPosition().z);
			camera->setPosition(pos);
			pos = this->environment->checkCollision(camera->getPosition());
			camera->setPosition(pos);

			// Update window
			windowOpengl->update();

		}
	}
	catch(const char* s)
	{
		throw s;
	}
}

// Check keypress and mouse position
void GameCore::checkKeyPress(){

	if((glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) ){
			this->running = false;
	}

	if(glfwGetKey('W'))
		camera->updatePosition(delta * translateSpeed * camera->getForward());
	else if(glfwGetKey('S'))
		camera->updatePosition(delta * translateSpeed * camera->getBackward());

	if(glfwGetKey('A'))
		camera->updatePosition(delta * translateSpeed * camera->getLeft());
	else if(glfwGetKey('D'))
		camera->updatePosition(delta * translateSpeed * camera->getRight());

	int tempX, tempY;
	glfwGetMousePos(&tempX, &tempY);
	glm::vec2 mouseDelta(tempX - mouseX, tempY - mouseY);
	mouseX = tempX;
	mouseY = tempY;
	camera->updateRotation(delta * rotationSpeed * mouseDelta.y, delta * rotationSpeed * mouseDelta.x);
}
