#pragma once

#include <afxwin.h>
#include <afxext.h>

class MainWin;

class DialogObjList : public CDialogBar
{
public:
	DialogObjList(MainWin* parentWnd)
		:
		parentWnd(parentWnd)
	{}
private:
	MainWin* parentWnd;

	//AFX_MSG functions
	afx_msg LRESULT OnWMCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void ol_objlist(){ OL_OBJLIST(); }

	void OL_OBJLIST();

	DECLARE_MESSAGE_MAP()
};