#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

class cGamepad
{
public:
	cGamepad(int playerNumber);
	XINPUT_STATE getState();
	bool isConnected();
	void vibrate(int leftValue = 0, int rightValue = 0);
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;
};

#endif