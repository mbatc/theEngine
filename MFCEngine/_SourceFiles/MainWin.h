#pragma once

#include <afxwin.h>
#include <afxext.h>

class D3DGraphics;

class MainWin : public CFrameWnd
{
	//Overides
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext);
	void OnSize(UINT nType, int cx, int cy);
public:
	MainWin();
	~MainWin();

	D3DGraphics * InitD3DView();

protected:
	//Methods
	BOOL InitDialogPointers();
	BOOL InitDialogControls();
	BOOL InitDockablePanels();

	//Data Members
	CMenu*		pMenu;
	CDialogBar* pObjProp;
	CDialogBar* pObjList;
	CSplitterWnd m_mainSplitter;
	BOOL m_bInitMainSplitter;

	D3DGraphics * gfx;

	//==========================================================
	//DIALOG CONTROLS
	//Object Properties
	CEdit * pObjXPOS;
	CEdit * pObjYPOS;
	CEdit * pObjZPOS;
	CEdit * pObjXROT;
	CEdit * pObjYROT;
	CEdit * pObjZROT;
	CEdit * pObjXSCL;
	CEdit * pObjYSCL;
	CEdit * pObjZSCL;
	CEdit * pObjNAME;
	CButton * pMFCBT;
	CButton * pNMLBT;

	//Object List
	CListBox * pObjLIST;

	//Message Map Methods
	afx_msg void MenuExit(){ MENUEXIT(); }
	afx_msg void WindowObjProperties(){ WINDOWOBJPROPERTIES(); }
	afx_msg void op_xpos(){ OP_XPOS(); }
	afx_msg void op_ypos(){ OP_YPOS(); }
	afx_msg void op_zpos(){ OP_ZPOS(); }
	afx_msg void op_xrot(){ OP_XROT(); }
	afx_msg void op_yrot(){ OP_YROT(); }
	afx_msg void op_zrot(){ OP_ZROT(); }
	afx_msg void op_xscl(){ OP_XSCL(); }
	afx_msg void op_yscl(){ OP_YSCL(); }
	afx_msg void op_zscl(){ OP_ZSCL(); }
	afx_msg void ol_objlist(){ OL_OBJLIST(); }

private:
	void MENUEXIT();
	void WINDOWOBJPROPERTIES();
	void OP_XPOS();
	void OP_YPOS();
	void OP_ZPOS();
	void OP_XROT();
	void OP_YROT();
	void OP_ZROT();
	void OP_XSCL();
	void OP_YSCL();
	void OP_ZSCL();
	void OL_OBJLIST();

	DECLARE_MESSAGE_MAP();
};