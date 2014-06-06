/*
 * Hall.cpp
 *
 *  Created on: May 14, 2014
 *      Author: rafel
 */

#include "Hall.h"

// Sets the hall position
void Hall::setPosition(glm::vec3 position){
	this->position = position;
	buildBody();
}

// Places the images in right position
Hall::Hall(glm::mat4 projMatrix) {
	this->projMatrix = projMatrix;
	edges.leftEdge=-1;
	edges.rightEdge=-1;
	textureID = bind2DTexture("matrix.png");
	position = glm::vec3(0,0,0);

	image = new Image(textureID,projMatrix);
	image->enableAnimation(glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.5f));

	image2 = new Image(textureID,projMatrix);
	image2->enableAnimation(glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.5f));

	image3 = new Image(textureID,projMatrix);
	image3->enableAnimation(glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.5f));

	image4 = new Image(textureID,projMatrix);
	image4->enableAnimation(glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.5f));

	image5 = new Image(textureID,projMatrix);
	image5->enableAnimation(glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.5f));
	buildBody();
}

// Builds the body of the hall
void Hall::buildBody(){

	//Left
	image->resetModel();
	glm::vec3 pos1 = glm::vec3(0,0,-1);
	image->translate(position);
	image->rotate(rotationAngle,glm::vec3(0,1,0));
	image->translate(pos1);
	image->rotate(180,glm::vec3(0,0,1));
	image->scale(2,1);



	//Right
	image2->resetModel();
	glm::vec3 pos2 = glm::vec3(0,0,1);
	image2->translate(position);
	image2->rotate(rotationAngle,glm::vec3(0,1,0));
	image2->translate(pos2);
	image2->rotate(180,glm::vec3(0,0,1));
	image2->scale(2,1);

	//Top
	image3->resetModel();
	glm::vec3 pos3 = glm::vec3(1,1,0);
	image3->translate(position);
	image3->rotate(rotationAngle,glm::vec3(0,1,0));
	image3->translate(pos3);
	image3->rotate(180,glm::vec3(0,0,1));
	image3->rotate(90,glm::vec3(1,0,0));
	image3->scale(3,1);



	//Bottom
	image4->resetModel();
	glm::vec3 pos4 = glm::vec3(1,-1,0);
	image4->translate(position);
	image4->rotate(rotationAngle,glm::vec3(0,1,0));
	image4->translate(pos4);
	image4->rotate(180,glm::vec3(0,0,1));
	image4->rotate(90,glm::vec3(1,0,0));
	image4->scale(3,1);

	//Lock
	image5->resetModel();
	glm::vec3 pos5 = glm::vec3(4,0,0);
	image5->translate(position);
	image5->rotate(rotationAngle,glm::vec3(0,1,0));
	image5->translate(pos5);
	image5->rotate(180,glm::vec3(0,0,1));
	image5->rotate(90,glm::vec3(0,1,0));
	image5->scale(1,1);
}

Hall::~Hall() {
	delete image;
	delete image2;
	delete image3;
	delete image4;
	delete image5;
}

// Draw
void Hall::draw(glm::mat4 cameraPosition, float delta){
	image->draw(cameraPosition,delta);
	image2->draw(cameraPosition,delta);
	image3->draw(cameraPosition,delta);
	image4->draw(cameraPosition,delta);
	image5->draw(cameraPosition,delta);
}

// Checks collision
glm::vec3 Hall::checkCollision(glm::vec3 cameraPosition){
	glm::vec3 tempNewCameraPosition = cameraPosition;
	if(image->doesCubeIntersectSphere(tempNewCameraPosition,0.4f)){
		tempNewCameraPosition= image->newCameraPosition;
		//return true;
	}
	if(image2->doesCubeIntersectSphere(tempNewCameraPosition,0.4f)){
		tempNewCameraPosition = image2->newCameraPosition;
		//return true;
	}
	if(image5->doesCubeIntersectSphere(tempNewCameraPosition,0.4f)){
		tempNewCameraPosition = image5->newCameraPosition;
	}

	return tempNewCameraPosition;
}

// If camera are inside the hall
bool Hall::cameraInside(glm::vec3 cameraPosition){


	return image4->isCameraOnIt(cameraPosition);

	if((cameraPosition.z>image->position.z&&cameraPosition.z<image2->position.z)||
			(cameraPosition.z<image->position.z&&cameraPosition.z>image2->position.z))
	{
return true;
		if((cameraPosition.x>image4->position.x-image4->height&&cameraPosition.x<image4->position.x+image4->height)||
				(cameraPosition.x<image4->position.x-image4->height&&cameraPosition.x>image4->position.x+image4->height))
		{
			return true;
		}
	}
	return false;
}

//Bind a 2D texture to OpenGL.
GLuint Hall::bind2DTexture(std::string filename)
{
	ILuint ilTextureID;
	ILboolean success;
	GLuint glTextureID;

	if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
		return -1;

	ilInit();
	ilGenImages(1, &ilTextureID);
	ilBindImage(ilTextureID);
	success = ilLoadImage((const ILstring)(std::string(TEXTURE_FILE_PATH) + filename).c_str());

	if(success)
	{
		glGenTextures(1, &glTextureID);
		glBindTexture(GL_TEXTURE_2D, glTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		ilDeleteImages(1, &ilTextureID);
	}
	else
		return -1;

	return glTextureID;
}

// Translate
void Hall::translate(glm::vec3 pos){
	image->translate(pos);
	image2->translate(pos);
	image3->translate(pos);
	image4->translate(pos);
	image5->translate(pos);

}

// Rotate
void Hall::rotate(float angle){
	this->rotationAngle = angle;
	buildBody();
}
