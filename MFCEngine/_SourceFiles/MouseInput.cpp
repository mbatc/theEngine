#include "MouseInput.h"

MouseServer::MouseServer()
{
	LeftBt.isDown = false;
	LeftBt.isPressed = false;
	LeftBt.isReleased = false;
	LeftBt.nFramesDown = 0;
	LeftBt.nFramesUp = 0;

	RightBt.isDown = false;
	RightBt.isPressed = false;
	RightBt.isReleased = false;
	RightBt.nFramesDown = 0;
	RightBt.nFramesUp = 0;
}

MouseServer::~MouseServer()
{

}

void MouseServer::LeftMousePressed()
{
	LeftBt.isDown = true;
	if (LeftBt.nFramesDown == 0)
	{
		LeftBt.isPressed = true;
	}
	LeftBt.nFramesDown++;
	LeftBt.nFramesUp = 0;
}

void MouseServer::RightMousePressed()
{
	RightBt.isDown = true;
	if (RightBt.nFramesDown == 0)
	{
		RightBt.isPressed = true;
	}
	RightBt.nFramesDown++;
	RightBt.nFramesUp = 0;
}

void MouseServer::RightMouseReleased()
{
	RightBt.isDown = false;
	if (RightBt.nFramesUp == 0)
	{
		RightBt.isReleased = true;
	}
	RightBt.nFramesUp++;
	RightBt.nFramesDown = 0;
}

void MouseServer::LeftMouseReleased()
{
	LeftBt.isDown = false;
	if (LeftBt.nFramesUp == 0)
	{
		LeftBt.isReleased = true;
	}
	LeftBt.nFramesUp++;
	LeftBt.nFramesDown = 0;
}

void MouseServer::Update()
{
	LeftBt.isPressed = false;
	LeftBt.isReleased = false;
	RightBt.isPressed = false;
	RightBt.isReleased = false;

	prevMouseX = mouseX;
	prevMouseY = mouseY;
}