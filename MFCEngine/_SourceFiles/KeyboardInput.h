#pragma once

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
	KeyboardServer();

	void Update();
	void KeyDown(char keyCode);
	void KeyUp(char keyCode);

private:
	KEYSTATE keyState[256];
};

class KeyboardClient
{
public:
	KeyboardClient();
	void ServerRef(KeyboardServer* server){ kServ = server; }

	bool KeyIsDown(char keyCode){ return kServ->keyState[keyCode].isDown; }
	bool KeyIsReleased(char keyCode){ return kServ->keyState[keyCode].isReleased; }
	bool KeyIsPressed(char keyCode){ return kServ->keyState[keyCode].isPressed; }
private:
	KeyboardServer* kServ;
};