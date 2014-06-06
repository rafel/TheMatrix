#include "Camera.h"
#include <GL/glfw.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fovY, float aspectRatio, float zNear, float zFar, glm::vec3 position)
	: fovY(fovY), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar), 
	position(position), phiAngle(0.0f), thetaAngle(0.0f)
{
}

//Return the current position.
glm::vec3 Camera::getPosition() const
{
	return position;
}

//Set position.
void Camera::setPosition(glm::vec3& position)
{
	this->position = position;
}

//Update the current position.
void Camera::updatePosition(const glm::vec3& posToUpdate)
{
	position += posToUpdate;
}

//Return the rotation matrix.
glm::mat4 Camera::getRotation() const
{
	//Identity matrix.
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, thetaAngle, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, phiAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	return rotation;
}

//Update the angles for the rotation matrix.
void Camera::updateRotation(float thetaAngle, float phiAngle)
{
	this->thetaAngle += thetaAngle;
	//Prevent a somersault about the x-axis.
	if(this->thetaAngle < -60.0f)
		this->thetaAngle = -60.0f;
	if(this->thetaAngle > 60.0f)
		this->thetaAngle = 60.0f;
	//if(this->thetaAngle > 45.0f)
	//	this->thetaAngle = 45.0f;

	this->phiAngle += phiAngle;
	if(this->phiAngle < 0.0f)
		this->phiAngle += 360.0f;
	if(this->phiAngle > 360.0f)
		this->phiAngle -= 360.0f;
}

//X-axis = strafe right.
glm::vec3 Camera::getRight() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

//X-axis = strafe left.
glm::vec3 Camera::getLeft() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f));
}

//Y-axis = go up.
glm::vec3 Camera::getUp() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

//Y-axis = go down.
glm::vec3 Camera::getDown() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
}

//Z-axis = backward.
glm::vec3 Camera::getBackward() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

//Z-axis = forward.
glm::vec3 Camera::getForward() const
{
	return glm::vec3(glm::inverse(getRotation()) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
}

//Projection matrix: Mapping 3D vertices to a 2D image plane.
glm::mat4 Camera::getProjMatrix() const
{
	return glm::perspective(fovY, aspectRatio, zNear, zFar);
}

//View matrix: Translates and rotates objects to place them in camera space.
//Affects and places everything relative to the camera.
glm::mat4 Camera::getViewMatrix() const
{
	return getRotation() * glm::translate(glm::mat4(1.0f), -position);
}

//Returns the PV matrix.
glm::mat4 Camera::getProjViewMatrix() const
{
	return getProjMatrix() * getViewMatrix();
}

//returns where "the camera is looking"
glm::vec3 Camera::getCameraDirection()
{
	bulletRayPosition = glm::vec3(0,0,-1);
	//position + glm::vec3(0,0,-0.001);
	glm::mat4 tempmat4 = glm::inverse(getRotation());
	glm::vec4 tempvec4 =tempmat4 * glm::vec4(bulletRayPosition,1); 
	bulletRayRotation = glm::vec3(tempvec4.x,tempvec4.y,tempvec4.z);

	return bulletRayRotation;
}
