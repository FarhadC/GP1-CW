/*
==================================================================================
zombieGame.cpp
==================================================================================
*/

#include "zombieGame.h"

vector<cTexture*> theGameTextures;
vector<cZombie*> theZombies;
vector<cBullet*> thePlayerBullets;
//Players score = 0 to begin with
int score = 0;