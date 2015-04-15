/*
=================
cPlayer.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
//Include gamepad header class
#include "cPlayer.h"
#include "cGamepad.h"

//create new player
cGamepad* player1;

void cPlayer::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/
//Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A
void cPlayer::update(float deltaTime)
{
	//new player (1)
	player1 = new cGamepad(1);

	//if press right key or dpad right, rotate +ve
	if (m_InputMgr->isKeyDown(VK_RIGHT) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT )
	{
		spriteRotation += 5.0f;
	}
	//if press left key or dpad left, rotate -ve
	if (m_InputMgr->isKeyDown(VK_LEFT) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		spriteRotation -= 5.0f;
	}
	//if press up key or dpad up, move direction +ve
	if (m_InputMgr->isKeyDown(VK_UP) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		spriteTranslation = (glm::vec2(2.0f, 2.0f));
	}
	//if press down key or dpad down, move direction -ve
	if (m_InputMgr->isKeyDown(VK_DOWN) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		spriteTranslation = -(glm::vec2(2.0f, 2.0f));
	}
	//although it serves no real purpose, if press A key or X button scale +ve
	if (m_InputMgr->isKeyDown(int('A')) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		spriteScaling += 0.2f;
	}
	//And if press S key or Y button scale -ve
	if (m_InputMgr->isKeyDown(int('S')) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	{
		spriteScaling -= 0.2f;
	}
	//if press space key or right should button (RB), shoot bullets
	if (m_InputMgr->isKeyDown(VK_SPACE) || player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		//player1->getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER
	{
		//player1->vibrate(65535, 65535);
		// Add new bullet sprite to the vector array
		thePlayerBullets.push_back(new cBullet);
		int numBullets = thePlayerBullets.size() - 1;
		thePlayerBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x , spritePos2D.y));
		thePlayerBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		thePlayerBullets[numBullets]->setTexture(theGameTextures[4]->getTexture());
		thePlayerBullets[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
		thePlayerBullets[numBullets]->setSpriteCentre();
		thePlayerBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		thePlayerBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		thePlayerBullets[numBullets]->setActive(true);
		thePlayerBullets[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		//Small delay when firing so sounds come out properly
		Sleep(40);
		
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	playerVelocity += spriteVelocityAdd;

	spritePos2D += playerVelocity * deltaTime;

	playerVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterator = thePlayerBullets.begin(); bulletIterator != thePlayerBullets.end(); ++bulletIterator)
	{
		(*bulletIterator)->update(deltaTime);
		for (vector<cZombie*>::iterator zombieIterator = theZombies.begin(); zombieIterator != theZombies.end(); ++zombieIterator)
		{
			if ((*zombieIterator)->collidedWith((*zombieIterator)->getBoundingRect(), (*bulletIterator)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				//Everytime bullet hits zombie, health -1 and also add 10 to players score
				(*zombieIterator)->setHealth(((*zombieIterator)->getHealth()) - 1);
				if ((*zombieIterator)->getHealth() < 1)
				{
					(*zombieIterator)->setActive(false);
				}
				(*bulletIterator)->setActive(false);
				score += 10;
			}
		}
	}

	vector<cBullet*>::iterator bulletIterator = thePlayerBullets.begin();
	while (bulletIterator != thePlayerBullets.end())
	{
		if ((*bulletIterator)->isActive() == false)
		{
			bulletIterator = thePlayerBullets.erase(bulletIterator);
			// play the bullet impact sound.
			m_SoundMgr->getSnd("Impact")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterator)->update(deltaTime);
			(*bulletIterator)->render();
			++bulletIterator;
		}
	}
}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cPlayer::setPlayerVelocity(glm::vec2 playerVel)
{
	playerVelocity = playerVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cPlayer::getPlayerVelocity()
{
	return playerVelocity;
}
