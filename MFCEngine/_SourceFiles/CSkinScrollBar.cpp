#include "CSkinScrollBar.h"

CSkinScrollBar::CSkinScrollBar()
{
	m_hBmp = NULL;
	m_bDrag = FALSE;
	memset(&m_si, 0, sizeof(SCROLLINFO));
	m_si.nTrackPos = -1;
	m_uClicked = -1;
	m_bNotify = FALSE;
	m_uHtPrev = -1;
	m_bPause = FALSE;
	m_bTrace = FALSE;
}

CSkinScrollBar::~CSkinScrollBar()
{
}

BOOL CSkinScrollBar::IsVertical()
{
	DWORD dwStyle = GetStyle();
	return dwStyle&SBS_VERT;
}

void CSkinScrollBar::SetBitmap(HBITMAP hBmp)
{
	ASSERT(m_hWnd);
	m_hBmp = hBmp;
	BITMAP bm;
	GetObject(hBmp, sizeof(bm), &bm);
	m_nWid = bm.bmWidth / 9;
	m_nFrmHei = bm.bmHeight / 3;
	CRect rc;
	GetWindowRect(&rc);
	GetParent()->ScreenToClient(&rc);
	if (IsVertical())
	{
		rc.right = rc.left + m_nWid;
	}
	else
	{
		rc.bottom = rc.top + m_nWid;
	}
	MoveWindow(&rc);

}