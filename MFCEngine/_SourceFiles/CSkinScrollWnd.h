#pragma once

#include <afxwin.h>

#include "CSkinScrollBar.h"

class CSkinScrollWnd : public CWnd
{
public:
	CSkinScrollWnd();
	~CSkinScrollWnd();

	BOOL SkinWindow(CWnd* pWnd, HBITMAP hBmpScroll);

private:
	HBITMAP m_hBmpScroll;
	CSkinScrollBar m_sbHorz, m_sbVert;
	CWnd	m_WndLimit;
	int m_nScrollWid;

	BOOL		m_bOp;
	int			m_nAngleType;
	
public:
	WNDPROC		m_funOldProc;

	DECLARE_MESSAGE_MAP();
};

extern BOOL UnskinWndScroll(CWnd *pWnd);