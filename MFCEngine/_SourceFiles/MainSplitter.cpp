#include "MainSplitter.h"
#include "MainApp.h"
#include "MainWin.h"
#include "GlobalPointers.h"


BOOL MainSplitter::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		theApp->LockKBD();
		((MainWin*)theApp->m_pMainWnd)->kServ->KeyDown(pMsg->wParam);
		theApp->UnlockKBD();
		return TRUE;
		break;
	case WM_KEYUP:
		theApp->LockKBD();
		((MainWin*)theApp->m_pMainWnd)->kServ->KeyUp(pMsg->wParam);
		theApp->UnlockKBD();
		return TRUE;
		break;
	default:
		return CWnd::PreTranslateMessage(pMsg);
	}
	return FALSE;
}


void MainSplitter::SetAppPointer(MainApp* app)
{
	theApp = app;
}