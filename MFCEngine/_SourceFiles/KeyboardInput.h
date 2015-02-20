#pragma once
#include <Windows.h>

struct KEYSTATE
{
	bool isDown;
	bool isPressed;
	bool isReleased;
	bool nFramesDown;
	bool nFramesUp;
};

class KeyboardClient;

class KeyboardServer
{
	friend KeyboardClient;
public:
	void Update();
	void KeyDown(char keyCode);
	void KeyUp(char keyCode);

private:
	KEYSTATE keyState[256];
};

class KeyboardClient
{
public:
	KeyboardClient(KeyboardServer& kserv);

	bool KeyIsDown(char keyCode){ return kServ.keyState[keyCode].isDown; }
	bool KeyIsReleased(char keyCode){ return kServ.keyState[keyCode].isReleased; }
	bool KeyIsPressed(char keyCode){ return kServ.keyState[keyCode].isPressed; }
private:
	KeyboardServer& kServ;
};