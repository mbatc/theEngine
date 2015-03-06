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
	case WM_LBUTTONDOWN:
		theApp->LockMSE();
		((MainWin*)theApp->m_pMainWnd)->mServ->LeftMousePressed();
		theApp->UnlockMSE();
		break;
	case WM_LBUTTONUP:
		theApp->LockMSE();
		((MainWin*)theApp->m_pMainWnd)->mServ->LeftMouseReleased();
		theApp->UnlockMSE();
		break;
	case WM_RBUTTONDOWN:
		theApp->LockMSE();
		((MainWin*)theApp->m_pMainWnd)->mServ->RightMousePressed();
		theApp->UnlockMSE();
		break;
	case WM_RBUTTONUP:
		theApp->LockMSE();
		((MainWin*)theApp->m_pMainWnd)->mServ->RightMouseReleased();
		theApp->UnlockMSE();
		break;
	case WM_MOUSEMOVE:	/*
		theApp->LockMSE();
		((MainWin*)theApp->m_pMainWnd)->mServ->OnMouseMove(GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam));
		theApp->UnlockMSE();*/
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