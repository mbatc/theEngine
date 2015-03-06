#pragma once

struct MouseEvent
{
	bool isDown;
	bool isPressed;
	bool isReleased;
	int nFramesDown;
	int nFramesUp;
};

class MouseClient;

class MouseServer
{
	friend MouseClient;
public:
	MouseServer();
	~MouseServer();

	void Update();
	void LeftMousePressed();
	void LeftMouseReleased();
	void RightMousePressed();
	void RightMouseReleased();

	void OnMouseMove(int x, int y){ prevMouseX = mouseX; mouseX = x; prevMouseY = mouseY; mouseY = y; }
private:

	int mouseX;
	int mouseY;

	int prevMouseX;
	int prevMouseY;

	MouseEvent LeftBt;
	MouseEvent RightBt;
};

class MouseClient
{
public:
	MouseClient():mServ(0){}
	~MouseClient(){}

	void SetServerPointer(MouseServer* server){ mServ = server; }

	bool isLeftMBDown()			{ if (mServ) return mServ->LeftBt.isDown; return false; }
	bool isRightMBDown()		{ if (mServ) return mServ->RightBt.isDown; return false;  }
	bool isRightMBPressed()		{ if (mServ) return mServ->RightBt.isReleased; return false; }
	bool isLeftMBPressed()		{ if (mServ) return mServ->LeftBt.isPressed; return false; }
	bool isRightMBReleased()	{ if (mServ) return mServ->RightBt.isReleased; return false; }
	bool isLeftMBReleased()		{ if (mServ) return mServ->LeftBt.isReleased; return false; }

	int GetMouseX(){ if (mServ) return mServ->mouseX; return -1; }
	int GetMouseY(){ if (mServ) return mServ->mouseY; return -1; }
	int GetPreviousMouseX(){ if (mServ) return mServ->prevMouseX; return -1; }
	int GetPreviousMouseY(){ if (mServ) return mServ->prevMouseY; return -1; }

private:
	MouseServer* mServ;
};