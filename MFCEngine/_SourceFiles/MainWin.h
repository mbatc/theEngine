#pragma once

#include "DialogObjProp.h"
#include "DialogObjList.h"
#include <afxwin.h>
#include <afxext.h>

class D3DGraphics;
class MainApp;

class MainWin : public CFrameWnd
{
	//Overides
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext);
	void OnSize(UINT nType, int cx, int cy);
public:
	MainWin(MainApp* app);
	~MainWin();

	D3DGraphics * InitD3DView();

	DialogObjProp* GetObjProp(){ return pObjProp; }
	DialogObjList* GetObjList(){ return pObjList; }

	MainApp* theApp;

	BOOL UpdateObjectList();

protected:
	//Methods
	BOOL InitDialogPointers();
	BOOL InitDialogControls();
	BOOL InitDockablePanels();

	//Data Members
	CMenu*			pMenu;
	DialogObjProp*	pObjProp;
	DialogObjList*	pObjList;
	CSplitterWnd	m_mainSplitter;
	BOOL			m_bInitMainSplitter;

	D3DGraphics * gfx;

	//Message Map Methods
	afx_msg void MenuExit(){ MENUEXIT(); }
	afx_msg void AddnewEmpty(){ ADDNEWEMPTY(); }
	afx_msg void WindowObjProperties(){ WINDOWOBJPROPERTIES(); }

private:
	void MENUEXIT();
	void ADDNEWEMPTY();
	void WINDOWOBJPROPERTIES();

	DECLARE_MESSAGE_MAP();
};