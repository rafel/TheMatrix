#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

#include <vector>
#include <fstream>
#include <iostream>
#include "graphicssettings.h"
#include <IL/il.h>
#include "Shader.h"

class Shadow;

class Image
{
public:

	Image(GLint,glm::mat4 projMatrix);
	~Image();
	bool inScreen();

	void enableAnimation(glm::vec2 startCrop,glm::vec2 endCrop);
	void drawShadow(float zPos,glm::mat4 projMatrix,glm::vec3 cameraPosition);
	void enableLight(bool);
	void draw(glm::mat4 cameraPosition, float delta);
	glm::vec3 position;
	glm::mat4 cameraPosition;
	glm::vec3 newCameraPosition;
	float secondRotationRadius;
	float width, height;
	float rotationAngle, secondRotationAngle;
	void blur(glm::vec2);
	void light(glm::vec2);
	void resetModel();

	glm::vec3 getRealPosition();
	float getRealRotationAngle();
	glm::vec3 getPixelPosition();
	glm::vec3 convertPixelPosToInGameCoord(glm::vec2 pixelPosition);
	bool checkCollision(glm::vec3 cameraPosition);
	GLuint bind2DTexture(std::string filename);
	void translate(glm::vec3);
	void rotate(float,glm::vec3);
	void scale(int width,int height);
	void cropTexture(glm::vec2,glm::vec2);
	glm::mat4 projMatrix;
	GLuint MatrixID;
	GLuint vertexPosition_modelspaceID;
	GLuint vertexColorID;
	glm::mat4 Model;
	inline float squared(float v) ;
	bool doesCubeIntersectSphere(glm::vec3 S, float);
	bool isCameraOnIt(glm::vec3 cameraPosition);
	//GLfloat vertices;
private:
	float animationMargin;
	bool animationEnabled;
	glm::vec2 startCrop,endCrop;
	float cropHeight;
	struct vertexInfo
	{
		glm::vec3 vertex;
		glm::vec2 textureCoord;
	};
	std::vector<vertexInfo> vertices;
	bool lightOn;
	glm::vec2 blurSize;
	glm::vec2 lightPosition;
	GLuint vboId;
	GLint vertexAttribLocation;
	GLint texCoordAttribLocation;
	GLint textureID;
	GLint textureLocation;
	GLint blurSizeLocation;
	GLint lightPositionLocation;
	GLint lightSizeLocation;
	GLint cameraPositionLocation;
	GLint projLocation;
	GLint zPosLocation;
	GLint scaleMatrixLocation;
	GLint translateMatrixLocation;
	GLint rotationMatrixLocation;

	glm::vec3 realPosition;

	Shader* shader;
};

#endif
