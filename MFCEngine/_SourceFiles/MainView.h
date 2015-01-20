#pragma once

#include <afxwin.h>
#include "MainDoc.h"

class MainView : public CView
{
	DECLARE_DYNCREATE(MainView)

	//Overides
	virtual void OnDraw(CDC * pDC);
public:
	MainView();
private:
};