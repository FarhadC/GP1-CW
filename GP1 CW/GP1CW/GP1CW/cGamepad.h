#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//Include windows and xinput to be able to use controller
#include <Windows.h>
#include <Xinput.h>

//compiler for library
#pragma comment(lib, "XInput.lib")

//xbox controller class definition
class cGamepad
{
public:
	//number of gamepad (can be up to 4)
	cGamepad(int playerNumber);
	//get state checks the input
	XINPUT_STATE getState();
	//check if controller is connected or not
	bool isConnected();
	//values for vibration, can go up to 65535, although couldnt get it to work properly
	void vibrate(int leftValue = 0, int rightValue = 0);
private:
	//holds the state of the controller
	XINPUT_STATE _controllerState;
	//holds reference as to which (0-3) controller is being stored
	int _controllerNum;
};

#endif