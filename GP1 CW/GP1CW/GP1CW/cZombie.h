/*
=================
cZombie.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _CZOMBIE_H
#define _CZOMBIE_H
#include "cSprite.h"

class cZombie : public cSprite
{
private:
	glm::vec2 asteroidVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Player update method
	void setAsteroidVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the player
	glm::vec2 getAsteroidVelocity();				 // Gets the player velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif