#pragma once

#include <afxwin.h>

class CSkinScrollBar : public CScrollBar
{
public:
	CSkinScrollBar();
	~CSkinScrollBar();

	HBITMAP	m_hBmp;
	int		m_nWid;
	int		m_nFrmHei;
	int		m_nHei;

	SCROLLINFO	m_si;
	BOOL		m_bDrag;
	CPoint		m_ptDrag;
	int			m_nDragPos;

	UINT		m_uClicked;
	BOOL		m_bNotify;
	UINT		m_uHtPrev;
	BOOL		m_bPause;
	BOOL		m_bTrace;

	void SetBitmap(HBITMAP hBmp);
	BOOL IsVertical();
	WNDPROC m_GetOldProc();
private:
};