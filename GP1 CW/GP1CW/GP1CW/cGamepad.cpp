#include "cGamepad.h"

cGamepad::cGamepad(int playerNumber)
{
	//Set the controller number
	_controllerNum = playerNumber - 1;
}

/*
// tried to input trigger and vibration but couldnt manage to get it working
typedef struct GAMEPAD
{
	WORD wButtons;
	byte bRightTrigger;

	void Reset()
	{
		bRightTrigger = 0.0f;
	}

};
*/

XINPUT_STATE cGamepad::getState()
{
	//zeros the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
	//get the state
	XInputGetState(_controllerNum, &_controllerState);
	//return it
	return _controllerState;
}

bool cGamepad::isConnected()
{
	//zeros the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
	//get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	//return "error success" as true, if isconnected() is successfull
	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cGamepad::vibrate(int leftValue, int rightValue)
{
	//create a vibration state
	XINPUT_VIBRATION Vibration;
	//zero it
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
	//set the vibration initial value
	Vibration.wLeftMotorSpeed = leftValue;
	Vibration.wRightMotorSpeed = rightValue;
	//vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}