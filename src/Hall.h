/*
 * Hall.h
 *
 *  Created on: May 14, 2014
 *      Author: rafel
 */

#ifndef OBJECT_H_
#define OBJECT_H_


#include "graphicssettings.h"

extern glm::vec3 ObjectPosition;
extern glm::vec2 ObjectLightSize;


#include "Image.h"

class Hall
{
public:
	Hall(glm::mat4 projMatrix);
	~Hall();

	struct edgesHalls
	{
		int leftEdge;
		int rightEdge;
		int back;
	} edges;
	//std::vector<edgesHalls> edges;

	void draw(glm::mat4 cameraPosition, float delta);
	void moveObjectX(float direction);
	void moveObjectY(float direction);
	void moveObjectZ(float direction);
	void moveObjectAngle(float angle);
	void rotateObject(float angleDirection);
	GLuint bind2DTexture(std::string filename);
	void translate(glm::vec3);
	void rotate(float);
	void scale(int width,int height);
	void buildBody();
	bool cameraInside(glm::vec3 cameraPosition);

	glm::vec3 checkCollision(glm::vec3 cameraPosition);
	void reset();

	void moveObject(glm::vec3 directions);
	bool inScreen();
	glm::vec3 getObjectPosition();

	void setPosition(glm::vec3 position);
	void setObjectBlur(bool value);
	glm::vec3 position;
	float rotationAngle;
	Image* image;
	Image* image2;
	Image* image3;
	Image* image4;
	Image* image5;
	GLint textureID;
	glm::mat4 projMatrix;
private:


};

#endif /* OBJECT_H_ */
