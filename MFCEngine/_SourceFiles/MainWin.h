#pragma once

#include "DialogObjProp.h"
#include "DialogObjList.h"
#include <afxwin.h>
#include <afxext.h>

class D3DGraphics;
class MainApp;

class MainWin : public CFrameWnd
{
	friend DialogObjList;
	friend DialogObjProp;

	//Overides
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext);
	void OnSize(UINT nType, int cx, int cy);
public:
	MainWin(MainApp* app);
	~MainWin();

	D3DGraphics * InitD3DView();
	void InitConsoleWindow();

	DialogObjProp* GetObjProp(){ return pObjProp; }
	DialogObjList* GetObjList(){ return pObjList; }

	MainApp* theApp;

	BOOL UpdateObjectList();

	CSplitterWnd	m_mainSplitter;

protected:
	//Methods
	BOOL InitDialogPointers();
	BOOL InitDialogControls();
	BOOL InitDockablePanels();

	//Data Members
	CMenu*			pMenu;
	DialogObjProp*	pObjProp;
	DialogObjList*	pObjList;
	CDialogBar*		pConsoleWindow;
	BOOL			m_bInitMainSplitter;

	const static UINT ID_CONSOLEEDIT = 11;
	const static UINT ID_CONSOLE = 10;

	D3DGraphics * gfx;

	//Message Map Methods
	afx_msg void MenuExit(){ MENUEXIT(); }
	afx_msg void AddnewCube(){ ADDNEWCUBE(); }
	afx_msg void AddnewPlane(){ ADDNEWPLANE(); }
	afx_msg void AddnewLight(){ ADDNEWLIGHT(); }
	afx_msg void AddnewEmpty(){ ADDNEWEMPTY(); }
	afx_msg void DeleteObject(){ DELETEOBJECT(); }
	afx_msg void WindowObjProperties(){ WINDOWOBJPROPERTIES(); }
	afx_msg void FilesaveasScene(){ FILESAVEASSCENE(); }

private:
	void MENUEXIT();
	void ADDNEWCUBE();
	void ADDNEWPLANE();
	void ADDNEWLIGHT();
	void ADDNEWEMPTY();
	void DELETEOBJECT();
	void WINDOWOBJPROPERTIES();
	void FILESAVEASSCENE();

	DECLARE_MESSAGE_MAP();
};