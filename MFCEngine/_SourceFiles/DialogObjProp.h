#pragma once

#include <afxwin.h>
#include <afxext.h>

class MainWin;

class DialogObjProp : public CDialogBar
{
public:
	DialogObjProp(MainWin* parentWnd)
		:
		parentWnd(parentWnd)
	{}
private:
	MainWin* parentWnd;

	//AFX_MSG functions
	afx_msg void op_xpos(){ OP_XPOS(); }
	afx_msg void op_ypos(){ OP_YPOS(); }
	afx_msg void op_zpos(){ OP_ZPOS(); }
	afx_msg void op_xrot(){ OP_XROT(); }
	afx_msg void op_yrot(){ OP_YROT(); }
	afx_msg void op_zrot(){ OP_ZROT(); }
	afx_msg void op_xscl(){ OP_XSCL(); }
	afx_msg void op_yscl(){ OP_YSCL(); }
	afx_msg void op_zscl(){ OP_ZSCL(); }
	afx_msg void op_objnme(){ OP_OBJNME(); }

	void OP_XPOS();
	void OP_YPOS();
	void OP_ZPOS();
	void OP_XROT();
	void OP_YROT();
	void OP_ZROT();
	void OP_XSCL();
	void OP_YSCL();
	void OP_ZSCL();
	void OP_OBJNME();

	DECLARE_MESSAGE_MAP()
};