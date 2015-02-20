#pragma once
#include <afxwin.h>
#include <afxext.h>
#include "resource.h"

class console
{
public:
	console()
		:
		outputWnd(NULL)
	{}
	void Output(char* msg)
	{ 
		if (outputWnd)
		{
			int msgLen = 0;
			for (; msg[msgLen] != '\0'; msgLen++);

			int bufLen = ((CEdit*)outputWnd->GetDlgItem(ID_CONSOLEEDIT))->GetWindowTextLengthA() +1;
			char* allText = new char[bufLen];
			char* buffer = new char[bufLen + msgLen + 1];
			((CEdit*)outputWnd->GetDlgItem(ID_CONSOLEEDIT))->GetWindowTextA(allText, bufLen);
			sprintf(buffer, "%s\r\n%s", allText, msg);
			((CEdit*)outputWnd->GetDlgItem(ID_CONSOLEEDIT))->SetWindowText(buffer);
		}
	};
	void LogError(UINT error){ lastError = error; }
	void SetEditPointer(CDialogBar* edit){ outputWnd = edit; }
private:
	UINT   lastError;
	CDialogBar* outputWnd;
};