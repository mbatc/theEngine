#include "KeyboardInput.h"

KeyboardServer::KeyboardServer()
{
	for (int i = 0; i < 256; i++)
	{
		keyState[i].isDown = false;
		keyState[i].isPressed = false;
		keyState[i].isReleased = false;
		keyState[i].nFramesDown = 0;
		keyState[i].nFramesUp = 0;
	}
}

void KeyboardServer::Update()
{
	for (int i = 0; i < 256; i++)
	{
		keyState[i].isPressed = false;
		keyState[i].isReleased = false;
	}
}

void KeyboardServer::KeyDown(char keyCode)
{
	keyState[keyCode].isDown = true;
	if (keyState[keyCode].nFramesDown == 0)
	{
		keyState[keyCode].isPressed = true;
	}
	keyState[keyCode].nFramesDown++;
	keyState[keyCode].nFramesUp = 0;
}

void KeyboardServer::KeyUp(char keyCode)
{
	keyState[keyCode].isDown = false;
	if (keyState[keyCode].nFramesUp == 0)
	{
		keyState[keyCode].isReleased = true;
	}
	keyState[keyCode].nFramesUp++;
	keyState[keyCode].nFramesDown = 0;
}

KeyboardClient::KeyboardClient()
	:
	kServ(nullptr)
{}

