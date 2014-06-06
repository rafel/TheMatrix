#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
	private:
		glm::vec3 position;
		float phiAngle;
		float thetaAngle;
		float fovY;
		float zNear;
		float zFar;
		float aspectRatio;
		glm::vec3 bulletRayPosition;
		glm::vec3 bulletRayRotation;
	public:
		Camera(float, float, float, float, glm::vec3);
		glm::vec3 getPosition() const;
		void setPosition(glm::vec3&);
		void updatePosition(const glm::vec3&);
		glm::mat4 getRotation() const;
		void updateRotation(float, float);
		glm::vec3 getRight() const;
		glm::vec3 getLeft() const;
		glm::vec3 getUp() const;
		glm::vec3 getDown() const;
		glm::vec3 getBackward() const;
		glm::vec3 getForward() const;
		glm::mat4 getProjViewMatrix() const;
		glm::mat4 getProjMatrix() const;
		glm::mat4 getViewMatrix() const;
		glm::vec3 getCameraDirection();
};

#endif CAMERA_H