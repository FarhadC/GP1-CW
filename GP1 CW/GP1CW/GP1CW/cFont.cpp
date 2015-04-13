/*
==========================================================================
cFont.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cFont.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/
cFont::cFont()
{
	theFont = NULL;
}
/*
==========================================================================
Overloaded constructor
==========================================================================
*/
cFont::cFont(LPCSTR fontFileName, int fontSize)
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}

/*
==========================================================================
Destructor
==========================================================================
*/
cFont::~cFont()
{
	delete theFont;
}
/*
==========================================================================
get the pointer to the font
==========================================================================
*/
FTFont* cFont::getFont()
{
	return theFont;
}

/*
==========================================================================
Render the text using the desired font
==========================================================================
*/
void cFont::printText(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();
	//changed text colour to red
	glColor3f(225.0f, 0.0f, 0.0f);
	//Moved the text. Translated by 5 on x and 20 on y
	//Also rotated by 180 degrees on x axis
	//Also scale the text to be big enough, scale by 1.5 in x and y
	glTranslatef(5.0f, 25.0f, 0.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glScalef(1.5f, 1.5f, 0.0f);
	theFont->Render(text, -1, textPos);

	glPopMatrix();
}