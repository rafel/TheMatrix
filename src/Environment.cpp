#include "Environment.h"
#include "Hall.h"
int prePreHall;

// Const, sets up the environment
Environment::Environment(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;
	currentHall=0;

	for (int i=0; i<MAX_HALLS; i++){
		theHalls[i] =  new Hall(this->projMatrix);
		theHalls[i]->setPosition(glm::vec3(20,9,20));
	}
	theHalls[0]->setPosition(glm::vec3(0,0,0));

	mergeHalls(0,1,2,7);
	mergeHalls(1,3,4,-1);
	mergeHalls(2,5,6,-1);
	mergeHalls(7,8,-1,-1);
	mergeHalls(8,9,10,-1);

}

// Mergehalls to a hall.
void Environment::mergeHalls(int theHall,int leftEdge,int rightEdge, int backEdge){

	//std::cout<<"merge: "<< theHall<<" "<<leftEdge<<" "<<rightEdge<<" "<< backEdge<<"\n";

	if(rightEdge!=-1)
	{
		glm::vec4 newPosRight =  glm::rotate(glm::mat4(1.0f),theHalls[theHall]->rotationAngle,glm::vec3(0.0f,1.0f,0.0f))*glm::vec4(3,0,3,1);
		theHalls[rightEdge]->setPosition(glm::vec3(newPosRight.x+theHalls[theHall]->position.x,newPosRight.y+theHalls[theHall]->position.y,newPosRight.z+theHalls[theHall]->position.z));
		theHalls[rightEdge]->rotate(theHalls[theHall]->rotationAngle-90);
		theHalls[rightEdge]->edges.back=theHall;
		theHalls[rightEdge]->edges.leftEdge=-1;
		theHalls[rightEdge]->edges.rightEdge=-1;
		theHalls[theHall]->edges.rightEdge = rightEdge;
	}
	if(leftEdge!=-1)
	{
		glm::vec4 newPosLeft = glm::rotate(glm::mat4(1.0f),theHalls[theHall]->rotationAngle,glm::vec3(0.0f,1.0f,0.0f))*glm::vec4(3,0,-3,1);
		theHalls[leftEdge]->setPosition(glm::vec3(newPosLeft.x+theHalls[theHall]->position.x,newPosLeft.y+theHalls[theHall]->position.y,newPosLeft.z+theHalls[theHall]->position.z));
		theHalls[leftEdge]->rotate(theHalls[theHall]->rotationAngle+90);

		theHalls[leftEdge]->edges.back=theHall;
		theHalls[leftEdge]->edges.leftEdge=-1;
		theHalls[leftEdge]->edges.rightEdge=-1;
		theHalls[theHall]->edges.leftEdge = leftEdge;
	}

	if(backEdge!=-1)
	{
		int dir = (int)((double) rand() / (RAND_MAX));
		int z = -3;
		int angle = -90;
		theHalls[backEdge]->edges.leftEdge=theHall;
		theHalls[backEdge]->edges.rightEdge=-1;
		if(dir == 0 )
		{
			z= 3;
			angle = 90;
			theHalls[backEdge]->edges.leftEdge=-1;
			theHalls[backEdge]->edges.rightEdge=theHall;

		}

		glm::vec4 newPosBack = glm::rotate(glm::mat4(1.0f),theHalls[theHall]->rotationAngle,glm::vec3(0.0f,1.0f,0.0f))*glm::vec4(-3,0,z,1);
		theHalls[backEdge]->setPosition(glm::vec3(newPosBack.x+theHalls[theHall]->position.x,newPosBack.y+theHalls[theHall]->position.y,newPosBack.z+theHalls[theHall]->position.z));
		theHalls[backEdge]->rotate(theHalls[theHall]->rotationAngle+angle);
		theHalls[backEdge]->edges.back = -1;
		theHalls[theHall]->edges.back= backEdge;
	}
}

// Removes all new objects
Environment::~Environment()
{
	for (int i=0; i<MAX_HALLS; i++){
		delete theHalls[i];
	}
}

// If we collide
glm::vec3 Environment::checkCollision(glm::vec3 cameraPosition){
	glm::vec3 tempCameraPos = cameraPosition;
	for (int i=0; i<MAX_HALLS; i++){
		tempCameraPos = theHalls[i]->checkCollision(tempCameraPos);
	}
	return tempCameraPos;
}

// Draw
void Environment::draw(glm::mat4 cameraPosition, float delta){
	this->delta = delta;
	this->cameraPosition = cameraPosition;


	this->drawStartScreen();

	for (int i=0; i<MAX_HALLS; i++){
		theHalls[i]->draw(cameraPosition,delta);
	}
}

// Find the needed halls
std::vector<int> Environment::findNeededHallsInTheRightPosition(int currentHall)
{
	int leftEdge = theHalls[currentHall]->edges.leftEdge;
	int rightEdge = theHalls[currentHall]->edges.rightEdge;
	int backEdge = theHalls[currentHall]->edges.back;
	std::vector<int> needed(MAX_HALLS);
//	std::vector<int>::iterator itterator = needed.begin();
	int itterator =0;
	for (itterator=0; itterator <MAX_HALLS; itterator++) {

		needed[itterator]=-1;
	}
	itterator = 0;

	needed[itterator] = currentHall;
	itterator++;
	if(leftEdge!=-1)
	{
		needed[itterator] =leftEdge;
		itterator++;
		if(theHalls[leftEdge]->edges.leftEdge!=-1)
		{
			needed[itterator] =theHalls[leftEdge]->edges.leftEdge;
			itterator++;
		}
		if(theHalls[leftEdge]->edges.rightEdge!=-1)
		{
			needed[itterator] =theHalls[leftEdge]->edges.rightEdge;
			itterator++;
		}
	}

	if(rightEdge!=-1)
	{
		needed[itterator] =rightEdge;
		itterator++;
		if(theHalls[rightEdge]->edges.leftEdge!=-1)
		{
			needed[itterator] =theHalls[rightEdge]->edges.leftEdge;
			itterator++;
		}
		if(theHalls[rightEdge]->edges.rightEdge!=-1)
		{
			needed[itterator] =theHalls[rightEdge]->edges.rightEdge;
			itterator++;
		}
	}

	if(backEdge!=-1)
	{
		needed[itterator] =backEdge;
		itterator++;
		int edgeNotYou =theHalls[backEdge]->edges.rightEdge;
		if(theHalls[backEdge]->edges.leftEdge!=currentHall)
			edgeNotYou = theHalls[backEdge]->edges.leftEdge;


		if(edgeNotYou!=-1)
		{
			needed[itterator] =edgeNotYou;
			itterator++;

			if(theHalls[edgeNotYou]->edges.leftEdge!=-1)
			{
				needed[itterator] =theHalls[edgeNotYou]->edges.leftEdge;
				itterator++;
			}
			if(theHalls[edgeNotYou]->edges.rightEdge!=-1)
			{
				needed[itterator] =theHalls[edgeNotYou]->edges.rightEdge;
				itterator++;
			}
		}


	}
	return needed;

}

// Find all free halls
std::vector<int> Environment::findAllFreeHalls( std::vector<int> neededHalls)
{
	std::vector<int> freeHalls(MAX_HALLS);
	for (int i  = 0; i < MAX_HALLS; i++) {
		freeHalls[i]=i;
	}
	for(int i =0;i<MAX_HALLS;i++)
	{
		if(neededHalls[i]!=-1)
			freeHalls[neededHalls[i]]=-1;
	}
	return freeHalls;

}

// Makes sure that all the halls are around you!
void Environment::update(glm::vec3 cameraPosition){
	for (int i=0; i<MAX_HALLS; i++){
		if(theHalls[i]->cameraInside(cameraPosition)){
			//std::cout << "theHalls["<< i << "]\n";
			if(i!=currentHall)
			{
				//std::cout <<i<<"\n";

				int newCurrentHall = i;
				std::vector<int> neededHalls = findNeededHallsInTheRightPosition(newCurrentHall);
				std::vector<int> freeHalls = findAllFreeHalls(neededHalls);
/*
				for (int it = 0; it < MAX_HALLS; it++) {
					std::cout<<freeHalls[it]<<" ";
				}
				std::cout<<"\n";
*/
				int leftEdge = theHalls[newCurrentHall]->edges.leftEdge;
				int rightEdge = theHalls[newCurrentHall]->edges.rightEdge;
				int backEdge = theHalls[newCurrentHall]->edges.back;

				if(leftEdge!=-1)
				{
					if(theHalls[leftEdge]->edges.leftEdge==-1)
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(leftEdge,freeHalls[it],-1,-1);

								//remove
								freeHalls[it]=-1;
								break;
							}
						}
					}
					if(theHalls[leftEdge]->edges.rightEdge==-1)
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(leftEdge,-1,freeHalls[it],-1);
								//remove
								freeHalls[it]=-1;
								break;
							}
						}
					}
				}
				else
				{
					//std::cout<<"noleft\n";
					////THIS CODE IS NOT DONE AND SHOULD NEVER HAPPEN!
					for (int it = 0; it < MAX_HALLS; it++)
					{
						if(freeHalls[it]!=-1)
						{
							//merge
							mergeHalls(newCurrentHall,freeHalls[it],-1,-1);
							//remove
							freeHalls[it]=-1;
							break;
						}

					}
				}

				if(rightEdge!=-1)
				{
					if(theHalls[rightEdge]->edges.leftEdge==-1)
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(rightEdge,freeHalls[it],-1,-1);
								//remove
								freeHalls[it]=-1;
								break;
							}

						}

					}
					if(theHalls[rightEdge]->edges.rightEdge==-1)
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(rightEdge,-1,freeHalls[it],-1);
								//remove
								freeHalls[it]=-1;
								break;
							}
						}
					}
				}
				else
				{
					//std::cout<<"noright\n";
					////THIS CODE IS NOT DONE AND SHOULD NEVER HAPPEN!
					for (int it = 0; it < MAX_HALLS; it++)
					{
						if(freeHalls[it]!=-1)
						{
							//merge
							mergeHalls(newCurrentHall,-1,freeHalls[it],-1);
							//remove
							freeHalls[it]=-1;
							break;
						}

					}
				}

				if(backEdge!=-1)
				{
					//std::cout<<"back: "<<backEdge<<"\n";

					int edgeNotYou =theHalls[backEdge]->edges.rightEdge;
					if(theHalls[backEdge]->edges.leftEdge!=newCurrentHall)
					edgeNotYou = theHalls[backEdge]->edges.leftEdge;


					if(edgeNotYou!=-1)
					{
						if(theHalls[edgeNotYou]->edges.leftEdge==-1)
						{
							for (int it = 0; it < MAX_HALLS; it++)
							{
								if(freeHalls[it]!=-1)
								{
									//merge
									mergeHalls(edgeNotYou,freeHalls[it],-1,-1);
									//remove
									freeHalls[it]=-1;
									break;
								}

							}

						}
						if(theHalls[edgeNotYou]->edges.rightEdge==-1)
						{
							for (int it = 0; it < MAX_HALLS; it++)
							{
								if(freeHalls[it]!=-1)
								{
									//merge
									mergeHalls(edgeNotYou,-1,freeHalls[it],-1);
									//remove
									freeHalls[it]=-1;
									break;
								}

							}

						}
					}
				}

				else
				{
					//std::cout<<"noback\n";
					for (int it = 0; it < MAX_HALLS; it++)
					{
						if(freeHalls[it]!=-1)
						{
							//merge
							mergeHalls(newCurrentHall,-1,-1,freeHalls[it]);
							//remove
							freeHalls[it]=-1;
							break;
						}

					}

					int edgeNotYou;
					if(theHalls[theHalls[newCurrentHall]->edges.back]->edges.leftEdge!=currentHall)
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(theHalls[newCurrentHall]->edges.back,freeHalls[it],-1,-1);
								edgeNotYou = theHalls[theHalls[newCurrentHall]->edges.back]->edges.leftEdge;
								//remove
								freeHalls[it]=-1;
								break;
							}

						}
					}
					else
					{
						for (int it = 0; it < MAX_HALLS; it++)
						{
							if(freeHalls[it]!=-1)
							{
								//merge
								mergeHalls(theHalls[newCurrentHall]->edges.back,-1,freeHalls[it],-1);
								edgeNotYou = theHalls[theHalls[newCurrentHall]->edges.back]->edges.rightEdge;
								//remove
								freeHalls[it]=-1;
								break;
							}

						}
					}
					for (int it = 0; it < MAX_HALLS; it++)
					{
						if(freeHalls[it]!=-1)
						{
							//merge
							mergeHalls(edgeNotYou,-1,freeHalls[it],-1);
							//remove
							freeHalls[it]=-1;
							break;
						}

					}
					for (int it = 0; it < MAX_HALLS; it++)
					{
						if(freeHalls[it]!=-1)
						{
							//merge
							mergeHalls(edgeNotYou,freeHalls[it],-1,-1);
							//remove
							freeHalls[it]=-1;
							break;
						}

					}
				}
			}
			//prePreHall = currentHall;
			currentHall = i;
		}
	}



}

// Game screen
void Environment::drawStartScreen(){

	// Enablue alpha to be able to blend pixels
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Disable blend
	glDisable(GL_BLEND);
}

// Sets projection matrix
void Environment::setProjMatrix(glm::mat4 projMatrix)
{
	this->projMatrix= projMatrix;
}

// Show game enviroment
void Environment::show(){
	glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

    //we tell opengl that we are using the entire window to draw.
    glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );
    //glOrtho(0,WINDOW_WIDTH,WINDOW_HEIGHT,0,0,1);
    glDisable(GL_DEPTH_TEST);




    //get back to drawing
    glMatrixMode( GL_MODELVIEW );

    //set the background color
    //glClearColor( 0.58f, 0.58f, 0.47f, 0.0f );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}
