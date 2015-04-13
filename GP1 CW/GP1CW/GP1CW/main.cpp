#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "zombieGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	//Create vector array of textures
	//Changed Textures to Zombies and gun's bullet
	LPCSTR texturesToUse[] = { "Images\\Zombie_1.png", "Images\\Zombie_2.png", "Images\\Zombie_3.png", "Images\\Zombie_1.png", "Images\\Bullet.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	//Changed 
	LPCSTR gameSounds[3] = { "Audio/Background.wav", "Audio/AK47_Shot.wav", "Audio/Zombie_Hit.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Impact", gameSounds[2]);

	// load game fontss
	// Load Fonts
	//Changed name "space age" to "ZOMBIE"
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/ZOMBIE.ttf" };

	//Changed "Space" to "ZOMBIE"
	//Changed text size from "24" to "35"
	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("ZOMBIE", gameFonts[1], 35);

	// Create vector array of textures
	//Changed (astro < 5) to (astro < 50). This is the number of zombies spawned at start
	//Changed random to 5+2 from 5+1 then 9+2
	for (int astro = 0; astro < 50; astro++)
	{
		theZombies.push_back(new cZombie);
		theZombies[astro]->setSpritePos(glm::vec2(windowWidth / (rand() % 9 + 2), windowHeight / (rand() % 9 + 2)));
		theZombies[astro]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
		int randAsteroid = rand() % 4;
		theZombies[astro]->setTexture(theGameTextures[randAsteroid]->getTexture());
		theZombies[astro]->setTextureDimensions(theGameTextures[randAsteroid]->getTWidth(), theGameTextures[randAsteroid]->getTHeight());
		theZombies[astro]->setSpriteCentre();
		theZombies[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theZombies[astro]->setActive(true);
		theZombies[astro]->setMdlRadius();
	}

	//Changed background texture to grass
	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\Background.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	cTexture textureEndBkgd;
	textureEndBkgd.createTexture("Images\\EndBackground.png");
	cBkGround spriteEndBkgd;
	spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteEndBkgd.setTexture(textureEndBkgd.getTexture());
	spriteEndBkgd.setTextureDimensions(textureEndBkgd.getTWidth(), textureEndBkgd.getTHeight());

	//Changed Rocket sprite to Player sprite
	//Changed spawn position of player to be further, used to be 512, now 700
	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\Player.png");
	cPlayer rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(700.0f, 380.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

	// Attach sound manager to rocket sprite
	rocketSprite.attachSoundMgr(theSoundMgr);

    //Play background audio before main loop
	theSoundMgr->getSnd("Theme")->playAudio(AL_TRUE);
	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events
		

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//If the player gets over 300 points, close the window
		if (score > 2500)
		{
			spriteEndBkgd.render();
			string s = to_string(score);
			LPCSTR lpStr = s.c_str();
			theFontMgr->getFont("ZOMBIE")->printText("Your Score was -", FTPoint(675.0f, -525.0f, 0.0f));
			theFontMgr->getFont("ZOMBIE")->printText(lpStr, FTPoint(975.0f, -525.0f, 0.0f));
		}
		else
		{
			spriteBkgd.render();

			rocketSprite.update(elapsedTime);

			vector<cZombie*>::iterator asteroidIterator = theZombies.begin();
			while (asteroidIterator != theZombies.end())
			{
				if ((*asteroidIterator)->isActive() == false)
				{
					asteroidIterator = theZombies.erase(asteroidIterator);
				}
				else
				{
					(*asteroidIterator)->update(elapsedTime);
					(*asteroidIterator)->render();
					++asteroidIterator;
				}
			}

			//Changed name of text from "Asteroids" to "Infected"
			//Replaced "Space" with "ZOMBIE"
			rocketSprite.render();
			//convert int score to string LPCSTR then substitute this into the printText method
			string s = to_string(score);
			LPCSTR lpStr = s.c_str();
			theFontMgr->getFont("ZOMBIE")->printText("Infected", FTPoint(0.0f, -1.0f, 0.0f));
			theFontMgr->getFont("ZOMBIE")->printText("Score -", FTPoint(290.0f, -1.0f, 0.0f));
			theFontMgr->getFont("ZOMBIE")->printText(lpStr, FTPoint(410.0f, -1.0f, 0.0f));
		}


		pgmWNDMgr->swapBuffers();
		//Commented this so out i could use multiple key inputs at the same time
		//theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
