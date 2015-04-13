/*
=================
cPlayer.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"
#include "zombieGame.h"

class cPlayer : public cSprite
{
private:
	glm::vec2 playerVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setPlayerVelocity(glm::vec2 playerVel);   // Sets the velocity for the rocket
	glm::vec2 getPlayerVelocity();				 // Gets the rocket velocity

};
#endif