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
	glm::vec2 zombieVelocity = glm::vec2(0.0f, 0.0f);
	//zombies have random health
	float health = (rand() % 10 + 1);


public:
	void render();		// Default render function
	void update(float deltaTime);		// Player update method
	void setZombieVelocity(glm::vec2 zombieVel);   // Sets the velocity for the player
	glm::vec2 getZombieVelocity();				 // Gets the player velocity
	//Constructor to set and get health
	void setHealth(float currentHealth);
	float getHealth();
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif