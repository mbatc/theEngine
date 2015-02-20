#include "KeyboardInput.h"

void KeyboardServer::Update()
{
	for (int i = 0; i < 256; i++)
	{
		keyState[i].isPressed = false;
		keyState[i].isDown = false;
	}
}

void KeyboardServer::KeyDown(char keyCode)
{
	keyState[keyCode].isDown = true;
	keyState[keyCode].isReleased = false;
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
	keyState[keyCode].isPressed = false;
	if (keyState[keyCode].nFramesUp == 0)
	{
		keyState[keyCode].isReleased = true;
	}
	keyState[keyCode].nFramesUp++;
	keyState[keyCode].nFramesDown = 0;
}