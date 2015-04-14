#include "cGamepad.h"


cGamepad::cGamepad(int playerNumber)
{
	_controllerNum = playerNumber - 1;
}

/*
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
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;

	
}

bool cGamepad::isConnected()
{
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

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
	XINPUT_VIBRATION Vibration;

	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	Vibration.wLeftMotorSpeed = leftValue;
	Vibration.wRightMotorSpeed = rightValue;

	XInputSetState(_controllerNum, &Vibration);
}