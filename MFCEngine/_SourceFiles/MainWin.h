#pragma once

#include <afxwin.h>
#include <afxext.h>
#include "MaterialEditor.h"
#include "DialogObjProp.h"
#include "DialogObjList.h"
#include "MainSplitter.h"
#include "TextEditor.h"

#include "KeyboardInput.h"
#include "MouseInput.h"

class D3DGraphics;
class MainApp;
class MaterialEditor;

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
	void OnMaterialEditorOK(D3DMATERIAL9 mat, char* textureName, int ObjID);

	MainApp* theApp;

	BOOL UpdateObjectList();

	MainSplitter	m_mainSplitter;

	KeyboardServer*	kServ;
	MouseServer* mServ;

protected:
	//Methods
	BOOL InitDialogPointers();
	BOOL InitDialogControls();
	BOOL InitDockablePanels();

	//Data Members
	MaterialEditor* materialEditor;
	CMenu*			pMenu;
	DialogObjProp*	pObjProp;
	DialogObjList*	pObjList;
	CDialogBar*		pConsoleWindow;
	BOOL			m_bInitMainSplitter;
	TextEditor*		scriptEditor;

	const static UINT ID_CONSOLE = 10;

	D3DGraphics * gfx;

	//Message Map Methods
	afx_msg void MenuExit(){ MENUEXIT(); }
	afx_msg void AddnewCube(){ ADDNEWCUBE(); }
	afx_msg void AddnewPlane(){ ADDNEWPLANE(); }
	afx_msg void AddnewLight(){ ADDNEWLIGHT(); }
	afx_msg void AddnewEmpty(){ ADDNEWEMPTY(); }
	afx_msg void AddnewCamera(){ ADDNEWCAMERA(); }
	afx_msg void AddnewMeshFromFile(){ ADDMESHFROMFILE(); }
	afx_msg void DeleteObject(){ DELETEOBJECT(); }
	afx_msg void WindowObjProperties(){ WINDOWOBJPROPERTIES(); }
	afx_msg void FilesaveasScene(){ FILESAVEASSCENE(); }
	afx_msg void AddComp_PlayerControl(){ ADDCOMP_PLAYERCONTROL(); }
	afx_msg void AddComp_Script(){ ADDCOMP_SCRIPT(); }
	afx_msg void EditMaterialEditor(){ EDITMATERIALEDITOR(); }

	afx_msg void OnRunGame() { ONRUNGAME(); }
	afx_msg void OnStopGame() { ONSTOPGAME(); }

private:
	void MENUEXIT();
	void ADDNEWCUBE();
	void ADDNEWPLANE();
	void ADDNEWLIGHT();
	void ADDNEWEMPTY();
	void ADDNEWCAMERA();
	void ADDMESHFROMFILE();
	void DELETEOBJECT();
	void WINDOWOBJPROPERTIES();
	void FILESAVEASSCENE();
	void ADDCOMP_PLAYERCONTROL(); 
	void ADDCOMP_SCRIPT();
	void EDITMATERIALEDITOR();

	void ONRUNGAME();
	void ONSTOPGAME();

	DECLARE_MESSAGE_MAP();
};