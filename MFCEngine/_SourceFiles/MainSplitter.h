#pragma once

#include <afxwin.h>
#include <afxext.h>

class MainApp;

class MainSplitter : public CSplitterWnd
{
public:
	MainSplitter(){}
	~MainSplitter(){}

	void SetAppPointer(MainApp* app);

private:

	MainApp* theApp;


	BOOL PreTranslateMessage(MSG* pMsg);
};