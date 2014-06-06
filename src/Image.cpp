#include "Image.h"
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GL/glfw.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

static const GLsizei VertexCount = 6;

void Image::enableAnimation(glm::vec2 startCrop,glm::vec2 endCrop)
{
	animationMargin =  (float)(rand()/RAND_MAX)*(0.0025f - 0.0015f)+0.0015f;
	animationMargin*=50;
	cropHeight=endCrop.y-startCrop.y;
	float startpercentage = (float)(rand()/RAND_MAX)*endCrop.y;
	animationEnabled = true;
	this->startCrop.y = startCrop.y+startpercentage;
	this->endCrop.y = endCrop.y+startpercentage;
	this->startCrop.x = startCrop.x;
	this->endCrop.x = endCrop.x;
}


// Draw image
void Image::draw(glm::mat4 cameraPosition, float delta)
{
	////animation

	if(animationEnabled)
	{

		startCrop.y-=animationMargin*delta;
		endCrop.y-=animationMargin*delta;
		if(startCrop.y<0)
		{
			endCrop.y =1.0f;
			startCrop.y = 1.0f-cropHeight;
		}
		cropTexture(startCrop,endCrop);
	}

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = projMatrix * cameraPosition * Model; // Remember, matrix multiplication is the other way around


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);


	shader->useProgram(true);

	 // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glUniform1i(textureLocation, 0);


		// bind VBOs for vertex array and index array
		glBindBuffer(GL_ARRAY_BUFFER,vboId);         // for vertex coordinates

		glEnableVertexAttribArray(vertexAttribLocation);

		//Number of bytes per vertex information. This tells us how many bytes each step takes.
		GLuint stride = sizeof(vertexInfo);

		//The offset in each step. float = 4 bytes.
		GLuint offset = 0 * 4;
		glVertexAttribPointer(vertexAttribLocation, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid *)offset);
		glEnableVertexAttribArray(texCoordAttribLocation);
		offset = 3 * 4;
		glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid *)offset);

		glDrawArrays(GL_TRIANGLES,0,VertexCount );
		glDisableVertexAttribArray(texCoordAttribLocation);
		glDisableVertexAttribArray(vertexAttribLocation);



		glBindBuffer(GL_ARRAY_BUFFER, 0);



	shader->useProgram(false);
}

void Image::translate(glm::vec3 pos){
	this->position = pos;
	Model= glm::translate(Model,pos);//translating to negative z-axis
}
void Image::rotate(float angle,glm::vec3 axis){
	rotationAngle = angle;
	Model = glm::rotate(Model,angle,axis);
}
void Image::scale(int width,int height){
	// Scale the model
	Model = glm::scale(Model,glm::vec3(width,height,0.0));
}

void Image::resetModel(){
	Model = glm::mat4(1.0f);
}

// Const. reset values. Bind 2dtexture
Image::Image(GLint texture,glm::mat4 projMatrix)
{
	animationEnabled=false;
	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);
	this->projMatrix = projMatrix;
	textureID = texture;
	position=glm::vec3(0,0,0);
	realPosition= position;

		vertices.resize(6);

		vertices[0].vertex.x=-1.0f;
		vertices[0].vertex.y=-1.0f;
		vertices[0].vertex.z=0.0f;

		vertices[0].textureCoord.x=0.0f;
		vertices[0].textureCoord.y=0.0f;

		vertices[1].vertex.x=1.0f;
		vertices[1].vertex.y=-1.0f;
		vertices[1].vertex.z=0.0f;

		vertices[1].textureCoord.x=1.0f;
		vertices[1].textureCoord.y=0.0f;

		vertices[2].vertex.x=1.0f;
		vertices[2].vertex.y=1.0f;
		vertices[2].vertex.z=0.0f;

		vertices[2].textureCoord.x=1.0f;
		vertices[2].textureCoord.y=1.0f;

		vertices[3].vertex.x=1.0f;
		vertices[3].vertex.y=1.0f;
		vertices[3].vertex.z=0.0f;

		vertices[3].textureCoord.x=1.0f;
		vertices[3].textureCoord.y=1.0f;

		vertices[4].vertex.x=-1.0f;
		vertices[4].vertex.y=1.0f;
		vertices[4].vertex.z=0.0f;

		vertices[4].textureCoord.x=0.0f;
		vertices[4].textureCoord.y=1.0f;

		vertices[5].vertex.x=-1.0f;
		vertices[5].vertex.y=-1.0f;
		vertices[5].vertex.z=0.0f;

		vertices[5].textureCoord.x=0.0f;
		vertices[5].textureCoord.y=0.0f;


		vboId = 0;


		// generate a new VBO and get the associated ID
		glGenBuffers(1, &vboId);

		// bind VBO in order to use
		glBindBuffer(GL_ARRAY_BUFFER, vboId);

		// upload data to VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo) * vertices.size(), &vertices[0], GL_STATIC_DRAW);




	shader = new Shader("imageVS.glsl", "imageFS.glsl");
	shader->setupShaders();

	vertexAttribLocation = shader->getAttribLocation("position");
	texCoordAttribLocation = shader->getAttribLocation("textureCoord");
	textureLocation = shader->getUniformLocation("textureWallpaper");

	// Get a handle for our "MVP" uniform
	MatrixID =  shader->getUniformLocation("MVP");

	// Get a handle for our buffers
	vertexPosition_modelspaceID = shader->getAttribLocation("vertexPosition_modelspace");


}

// Deconst.
Image::~Image()
{
    glDeleteBuffers(1, &vboId);
	delete shader;
}

// Return real position in world
glm::vec3 Image::getRealPosition()
{
	return realPosition;
}

// Crops the texture
void Image::cropTexture(glm::vec2 start,glm::vec2 end){

	vertices[0].textureCoord.x=start.x;
	vertices[0].textureCoord.y=start.y;

	vertices[1].textureCoord.x=end.x;
	vertices[1].textureCoord.y=start.y;

	vertices[2].textureCoord.x=end.x;
	vertices[2].textureCoord.y=end.y;

	vertices[3].textureCoord.x=end.x;
	vertices[3].textureCoord.y=end.y;

	vertices[4].textureCoord.x=start.x;
	vertices[4].textureCoord.y=end.y;

	vertices[5].textureCoord.x=start.x;
	vertices[5].textureCoord.y=start.y;
	// bind VBO in order to use
			glBindBuffer(GL_ARRAY_BUFFER, vboId);

			// upload data to VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo) * vertices.size(), &vertices[0], GL_STATIC_DRAW);


}
// Check collision for position with size
bool Image::checkCollision(glm::vec3 cameraPosition){
	float margin = 0.5f;
	if(cameraPosition.x + margin > position.x && cameraPosition.x < position.x ){
		return true;
	}
	return false;
}

// get real rotation angle
float Image::getRealRotationAngle()
{
	return rotationAngle+secondRotationAngle;
}

//Bind a 2D texture to OpenGL.
GLuint Image::bind2DTexture(std::string filename)
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

// Squared
inline float Image::squared(float v) { return v * v; }


// If we collide
bool Image::doesCubeIntersectSphere(glm::vec3 S, float R)
{
	glm::vec4 C1 = Model*glm::vec4(1,1,0,1);
	glm::vec4 C2 = Model*glm::vec4(-1,-1,0,1);

	// Are we in right X margin
//	std::cout<<"c1 x:"<<C1.x<<" c1 y:"<<C1.y<<" c1 z:"<<C1.z<<"\n";
//	std::cout<<"c2 x:"<<C2.x<<" c2 y:"<<C2.y<<" c2 z:"<<C2.z<<"\n";

	float margin = 0.1f;
	if((S.x+margin>=C1.x &&S.x-margin<=C2.x)||(S.x-margin<=C1.x && S.x+margin>=C2.x))
	{
		//Are we near Z of the wall
		if((S.z <C1.z && S.z+R>C1.z))
		{
			this->newCameraPosition = S;
			this->newCameraPosition.z = C1.z-R;
			return true;
		}
		else if((S.z >C1.z && S.z-R< C1.z))
		{
			this->newCameraPosition = S;
			this->newCameraPosition.z = C1.z+R;
			return true;
		}
	}
	else if((S.z+margin>=C1.z &&S.z-margin<=C2.z)||(S.z-margin<=C1.z &&S.z+margin>=C2.z))
	{
		if(S.x <C1.x && S.x+R> C1.x)
		{
			this->newCameraPosition = S;
			this->newCameraPosition.x = C1.x-R;
			return true;
		}
		else if(S.x >C1.x && S.x-R< C1.x)
		{
			this->newCameraPosition = S;
			this->newCameraPosition.x = C1.x+R;
			return true;
		}

	}

	return false;
}

// If camera is on the image
bool Image::isCameraOnIt(glm::vec3 cameraPosition)
{
	glm::vec4 C1 = Model*glm::vec4(1,1,0,1);
	glm::vec4 C2 = Model*glm::vec4(-1,-1,0,1);

	float margin = 0.1f;
		if((cameraPosition.x+margin>=C1.x &&cameraPosition.x-margin<=C2.x)||(cameraPosition.x-margin<=C1.x && cameraPosition.x+margin>=C2.x))
		{

			if((cameraPosition.z+margin>=C1.z &&cameraPosition.z-margin<=C2.z)||(cameraPosition.z-margin<=C1.z && cameraPosition.z+margin>=C2.z))
			{
				return true;
			}
		}
		return false;


	return false;

}
